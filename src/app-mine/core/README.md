# Independent Mine rules

mine.c owns board generation, first-click safety, cover/flag state, flood,
chord, win/loss and elapsed seconds. No host, graphics, input binding or XP
cell representation is present. The maximum board is30x20, with separate
600-byte hazard and cover arrays and a bounded automatic flood queue.
