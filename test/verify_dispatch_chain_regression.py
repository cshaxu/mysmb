from pathlib import Path
import subprocess,struct,json,csv,argparse
parser=argparse.ArgumentParser(description='T31 cross-chain diagnostics; failures are retained, never relabeled as ROM matches.')
parser.add_argument('directory',type=Path)
parser.add_argument('rom',type=Path)
args=parser.parse_args()
b=args.directory.resolve();rom=args.rom.resolve();rows=[]
assert b.is_relative_to((Path(__file__).resolve().parents[1]/'build').resolve())
def frames(p):
 d=p.read_bytes();n=struct.unpack_from('<I',d,8)[0];assert len(d)==12+n*4409 and n==4
 return [d[12+i*4409:12+(i+1)*4409] for i in range(n)]
def run(args):subprocess.run(list(map(str,args)),check=True,timeout=20,stdout=subprocess.DEVNULL)
for family,cases in [('game-entry',[0,1,2,3]),('engine-tail',[0,2,3]),('scroll',[0,5,19]),('entrance',[0,7,18])]:
 for case in cases:
  name=family+'-'+str(case);fixture='--fixture=t31-'+name.replace('-'+str(case),'='+str(case))
  rp=b/('cross-'+name+'.msfr');pc=b/('cross-'+name+'.csv')
  run([b/'reference.exe',rom,rp,4,0,'--warmup=1',fixture,'--pc-coverage='+str(pc)])
  original=frames(rp);widths=[];diffs=[]
  for bits in (32,64):
   np=b/('cross-'+name+'-'+str(bits)+'.msfr')
   run([b/('native%d.exe'%bits),np,4,0,1,'--warmup=1',fixture,'--bootstrap-title','0:0'])
   native=frames(np);widths.append(np.read_bytes());perframe=[]
   for frame,(a,c) in enumerate(zip(original,native)):
    ram=[i for i in range(8,2048) if not 0x100<=i<0x200 and a[4+i]!=c[4+i]]
    output=[i for i in range(2052,4409) if a[i]!=c[i]]
    perframe.append(dict(frame=frame,ramDifferences=len(ram),ramAddresses=[hex(i) for i in ram],outputDifferences=len(output)))
   diffs.append(dict(bits=bits,frames=perframe))
  assert widths[0]==widths[1],name
  with pc.open() as f:hits={int(r['pc'],16):int(r['hits']) for r in csv.DictReader(f)}
  joins={hex(p):hits.get(p,0) for p in [0xaedc,0xaeea,0xaefe,0xaf93,0xb04a,0xb069]}
  rows.append(dict(route=name,widthIdentical=True,originalJoins=joins,comparisons=diffs))
  print(name,'widths identical; first frame RAM/output deltas',diffs[0]['frames'][0]['ramDifferences'],diffs[0]['frames'][0]['outputDifferences'],flush=True)
raw=sum(p.stat().st_size for p in b.iterdir() if p.suffix in ('.bin','.msfr','.csv','.calls'))
assert raw<=2000000,raw
(b/'cross-chain.json').write_text(json.dumps(dict(routes=rows,rawBytes=raw,fullGameClaim=False),indent=2)+'\n')
print('Raw evidence bytes',raw)
