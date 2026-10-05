"""Report neutral executable sizes;optionally compare loader-visible PE contents."""
import argparse,hashlib,json,re,struct
from pathlib import Path

def inspect(path,cluster,map_path=None):
    data=path.read_bytes()
    u16=lambda at:struct.unpack_from('<H',data,at)[0]
    u32=lambda at:struct.unpack_from('<I',data,at)[0]
    if data[:2]!=b'MZ':raise ValueError('Not an MZ image')
    result={'fileBytes':len(data),'clusterBytes':cluster,
            'allocatedBytes':((len(data)+cluster-1)//cluster)*cluster,
            'sha256':hashlib.sha256(data).hexdigest()}
    pe=u32(60)
    if pe<len(data)-24 and data[pe:pe+4]==b'PE\0\0':
        opt=pe+24;count=u16(pe+6);table=opt+u16(pe+20)
        magic=u16(opt);directory=opt+(112 if magic==0x20b else 96)
        optional=bytearray(data[opt:table]);optional[64:68]=b'\0'*4
        sections=[]
        for i in range(count):
            at=table+i*40;raw_bytes=u32(at+16);raw_start=u32(at+20)
            sections.append({'name':data[at:at+8].split(b'\0')[0].decode('ascii'),
                'virtualBytes':u32(at+8),'rva':u32(at+12),'rawBytes':raw_bytes,
                'characteristics':u32(at+36),
                'rawSha256':hashlib.sha256(data[raw_start:raw_start+raw_bytes]).hexdigest()})
        end=max([u32(opt+60)]+[u32(table+i*40+20)+u32(table+i*40+16) for i in range(count)])
        result.update(format='PE',machine=u16(pe+4),entryRva=u32(opt+16),
            imageBase=struct.unpack_from('<Q' if magic==0x20b else '<I',data,opt+(24 if magic==0x20b else 28))[0],
            imageBytes=u32(opt+56),headerBytes=u32(opt+60),
            optionalHeaderSha256=hashlib.sha256(optional).hexdigest(),
            loaderCharacteristics=u16(pe+22)&~0x000c,
            symbolCount=u32(pe+16),symbolOffset=u32(pe+12),
            tailBytes=len(data)-end,sections=sections,
            stackReserve=struct.unpack_from('<Q' if magic==0x20b else '<I',data,opt+72)[0],
            loaderDirectories=data[directory:directory+128].hex())
        # Hex here represents only sixteen public PE address/size pairs,
        # never program/resource bytes. Tracked summaries need no raw payload.
    else:
        header=u16(8)*16;pages=u16(4);last=u16(2)
        declared=pages*512-(512-last if last else 0)
        result.update(format='DOS-MZ',headerBytes=header,declaredFileBytes=declared,
            imageFileBytes=declared-header,tailBytes=len(data)-declared,
            minimumExtraParagraphs=u16(10),maximumExtraParagraphs=u16(12),
            minimumLoaderBytes=((declared-header+15)//16+u16(10))*16,
            entryCs=u16(22),entryIp=u16(20),stackSs=u16(14),stackSp=u16(16),
            relocationCount=u16(6))
        if map_path:
            totals={};maximum=0
            for line in map_path.read_text(errors='replace').splitlines():
                match=re.match(r'\s*([0-9A-F]+)H\s+[0-9A-F]+H\s+([0-9A-F]+)H\s+\S+\s+(\S+)',line)
                if match:
                    start,length,kind=match.groups();length=int(length,16)
                    totals[kind]=totals.get(kind,0)+length
                    maximum=max(maximum,int(start,16)+length)
            result.update(mapClassBytes=totals,mapSegmentExtentBytes=maximum)
    return result

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--input',type=Path,required=True)
    parser.add_argument('--compare',type=Path)
    parser.add_argument('--map',type=Path)
    parser.add_argument('--cluster',type=int,default=512)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();root=Path(__file__).resolve().parents[1]
    if args.cluster<=0:raise ValueError('Cluster must be positive')
    if not args.output.resolve().is_relative_to(root/'build'):
        raise ValueError('Evidence must remain beneath build')
    record=inspect(args.input,args.cluster,args.map)
    if args.compare:
        before=inspect(args.compare,args.cluster,args.map)
        if record['format']!='PE' or before['format']!='PE':
            raise ValueError('Loader-section comparison requires PE images')
        keys=('machine','entryRva','imageBase','imageBytes','headerBytes',
              'sections','stackReserve','loaderDirectories','optionalHeaderSha256',
              'loaderCharacteristics')
        differences=[key for key in keys if record[key]!=before[key]]
        record.update(loaderDifferences=differences,beforeFileBytes=before['fileBytes'],
                      savedBytes=before['fileBytes']-record['fileBytes'])
        if differences:raise ValueError('Loader differences: '+','.join(differences))
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(record,indent=2)+'\n')
    print(json.dumps(record,indent=2))

if __name__=='__main__':main()
