#!/usr/bin/env python

import sys

with open(sys.argv[1], "r") as header:
    
    for line in header:
        
        line = line.strip()
        
        if not line: continue
        
        if line.startswith("//") or line.startswith("/*"): continue
        
        line = line.split("//")[0]
        
        print line
        
        
        
        
        
        
