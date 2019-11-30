clc; clear;
tic
syms x1(t) x2(t) x3(t) x4(t) y1(t) y2(t) mu vu b c f h A B UPH UPC PAP;

Qh = [
    b-c-f b-c-f -c-f 0;
    b-c-f-h b-c-f-h -c-f-h -h;
    b-f-A b-f-A -f-A 0;
    -h -h -h -h
];
    
Qc = [
    b-c-f 0 -c-f -c-f;
    -h -h -h -h;
    b-f-B 0 -f-B -f-B;
    b-f-B-h -h -f-B-h -f-B-h
];

Ph = [
    2*f 2*f 2*f 0;
    2*f 2*f 2*f 0;
    2*f 2*f 2*f 0;
    0 0 0 0
];

Pc= [
    2*f 0 2*f+B 2*f+B;
    0 0 0 0;
    2*f 2*f 2*f 0;
    2*f+B 2*f+B 2*(f+B) 2*(f+B)
];

R1 = y1(t) == 1 - y2(t);
R2 = x1(t) + x2(t) + x3(t) + x4(t) == 1.0;
R3 = x2(t) >= 0;
R4 = x3(t) >= 0;
R5 = x4(t) >= 0;
R6 = y1(t) >= 0;
R7 = y2(t) >= 0;

UPH = umpirePayoff(1,1, 1, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(2,1, 1, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(3,1, 1, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(4,1,1, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(2,3,1, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(2,4,1, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(3,4,1, x1(t), x2(t), x3(t), x4(t), Ph, Pc);
UPC = umpirePayoff(1,1, 2, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(2,1, 2, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(3,1, 2, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(4,1,2, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(2,3,2, x1(t), x2(t), x3(t), x4(t), Ph, Pc) + umpirePayoff(2,4,2, x1(t), x2(t), x3(t), x4(t), Ph, Pc)+ umpirePayoff(3,4,2, x1(t), x2(t), x3(t), x4(t), Ph, Pc);
PAP = playerPayoff(1,1, y1(t), Qh, Qc) + playerPayoff(2,1, y1(t), Qh, Qc) + playerPayoff(3,1, y1(t), Qh, Qc) + playerPayoff(4,1, y1(t), Qh, Qc) + playerPayoff(2,2, y1(t), Qh, Qc) +playerPayoff(2,3, y1(t), Qh, Qc) + playerPayoff(2,4, y1(t), Qh, Qc) + playerPayoff(3,3, y1(t), Qh, Qc) +playerPayoff(3,4, y1(t), Qh, Qc);

% odes = [ode1; ode2]
% [uSol(t), vSol(t)] = dsolve(odes)

EX1 = diff(x1) == x1 * ( x1 * playerPayoff(1,1, y1, Qh, Qc) + x2 * playerPayoff(1,2, y1, Qh, Qc)+ x3 * playerPayoff(1,3, y1, Qh, Qc) + x4 * playerPayoff(1,4, y1, Qh, Qc) - PAP ) - mu * x1 + mu *(1-x1)/3;
EX2 = diff(x2) == x2 * (x1 * playerPayoff(2,1, y1, Qh, Qc) + x2 * playerPayoff(2,2, y1, Qh, Qc)+ x3 * playerPayoff(2,3, y1, Qh, Qc) + x4  * playerPayoff(2,4, y1, Qh, Qc) - PAP) - mu * x1 + mu *(1-x1)/3;
EX3 = diff(x3) == x3 * (x1 * playerPayoff(3,1, y1, Qh, Qc) + x2 * playerPayoff(3,2, y1, Qh, Qc)+ x3 * playerPayoff(3,3, y1, Qh, Qc) + x4  * playerPayoff(3,4, y1, Qh, Qc) - PAP) - mu * x1 + mu *(1-x1)/3;
EX4 = diff(x4) == x4 * (x1 * playerPayoff(4,1, y1, Qh, Qc) + x2 * playerPayoff(4,2, y1, Qh, Qc)+ x3 * playerPayoff(4,3, y1, Qh, Qc) + x4  * playerPayoff(4,4, y1, Qh, Qc) - PAP) - mu * x1 + mu *(1-x1)/3;
EY1 = diff(y1) == y1 * (1 - y1) * (UPH - UPC) - vu * y1 + vu *(1-y1);

% playerAverage(y1, Qh, Qc)

% dsolve(EX1, EX2, EX3, EX4, EY1, R1, R2, UPH, UPC, PAP)
% eqs = [EX1; EX2; EX3; EX4; EY1; R1; R2; UPH; UPC; PAP];
% vars = [x1(t), x2(t), x3(t), x4(t), y1(t), y2(t), mu, vu, b, c, f, h, A, B];
% [eqs, vars, newVars] = reduceDifferentialOrder(eqs, vars)
UPH - UPC
toc

function result = xVariableToIndex(x1,x2,x3,x4,l)
    if l == 1
        result = x1;
    elseif l == 2
        result = x2;
    elseif l == 3
        result = x3;
    elseif l == 4
        result = x4;
    end 
end

function result = yVariableToIndex(y1, y2,l)
    if l == 1
        result = y1;
    elseif l == 2
        result = y2;
    end 
end

function result = playerAverage(y1, Qh, Qc)
    result = playerPayoff(1,1, y1, Qh, Qc) + playerPayoff(2,1, y1, Qh, Qc) + playerPayoff(3,1, y1, Qh, Qc) + playerPayoff(4,1, y1, Qh, Qc) + playerPayoff(2,2, y1, Qh, Qc) + playerPayoff(2,3, y1, Qh, Qc) + playerPayoff(2,4, y1, Qh, Qc) + playerPayoff(3,3,y1, Qh, Qc) + playerPayoff(3,4, y1, Qh, Qc) + playerPayoff(4,4, y1, Qh, Qc);
end

function result = umpirePayoff(i, j, k, x1, x2, x3, x4, Ph, Pc)
    if k == 1
       result = xVariableToIndex(x1, x2, x3, x4, i) * Ph(i,j) * xVariableToIndex(x1, x2, x3, x4, j);
    elseif k == 2
       result = xVariableToIndex(x1, x2, x3, x4, i) * Pc(i,j) * xVariableToIndex(x1, x2, x3, x4, j);
    end
end

function result = playerPayoff(i, j, y1, Qh, Qc)
   result = y1 * Qh(i,j) + (1-y1) * Qc(i,j);
end