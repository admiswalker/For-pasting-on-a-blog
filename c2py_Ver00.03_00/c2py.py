import sys # sys.stdout.write

def c2py_str(rhs, i):
    lhs = rhs[ i[0] ]
    i[0] += 1
    return lhs

def c2py_int(rhs, i):
    lhs = int(rhs[ i[0] ])
    i[0] += 1
    return lhs

def c2py_double(rhs, i):
    lhs = float(rhs[ i[0] ])
    i[0] += 1
    return lhs

def c2py_vecInt(rhs, i):
    size = int(rhs[ i[0] ])
    i[0] += 1
    
    vec = [int(0) for n in range(size)]
    for n in range(size):
        vec[n] = int(rhs[ i[0] ])
        i[0] += 1
    return vec

def c2py_vecDouble(rhs, i):
    size = int(rhs[ i[0] ])
    i[0] += 1
    
    vec = [0.0 for n in range(size)]
    for n in range(size):
        vec[n] = float(rhs[ i[0] ])
        i[0] += 1
    return vec

def c2py_vvecInt(rhs, i):
    row_size = int(rhs[ i[0] ])
    i[0] += 1

    vvec = [[] for p in range(row_size)]
    
    for p in range(row_size):
        col_size = int(rhs[ i[0] ])
        i[0] += 1
        
        vvec[p] = [int(0) for q in range(col_size)]
        
        for q in range(col_size):
            vvec[p][q] = int(rhs[ i[0] ])
            i[0] += 1
            
    return vvec

def c2py_vvecDouble(rhs, i):
    row_size = int(rhs[ i[0] ])
    i[0] += 1

    vvec = [[] for p in range(row_size)]
    
    for p in range(row_size):
        col_size = int(rhs[ i[0] ])
        i[0] += 1
        
        vvec[p] = [0.0 for q in range(col_size)]
        
        for q in range(col_size):
            vvec[p][q] = float(rhs[ i[0] ])
            i[0] += 1
            
    return vvec

def print_vec(vec):
    for q in range(len(vec)):
        sys.stdout.write("%8.3lf " % vec[q])
    sys.stdout.write("\n")

def print_vvec(vvec):
    for p in range(len(vvec)):
        for q in range(len(vvec[p])):
            sys.stdout.write("%8.3lf " % vvec[p][q])
        sys.stdout.write("\n")
