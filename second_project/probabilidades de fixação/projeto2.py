# -*- coding: utf-8 -*-
"""
Created on Mon Nov 18 18:25:23 2019

@author: Regina Duarte
"""
import numpy as np
###payoffs matrix unpire honesto : OC PC OD PD

def fit(s1,s2,j,umpire,Qh,Qc,N):
    if umpire=='c':
        return Qc[s1][s1]*(j-1)+Qc[s1][s2]
    else:
        return Qh[s1][s1]*(j-1)+Qh[s1][s2]
    
def fit_umpires(s,ump1, j, N,UMc, UMh):
    if ump=='c':
        return (j-1)*UMc[s]+(N-j)*UMh[s]
    else:
        return (j-1)*UMh[s]+(N-j)*UMc[s]
        
        
    
def markovMatrix(N, f, b, B, A, h, c,beta):
    Qh=np.array([[b-c-f, b-c-f, -c-f, 0],[b-c-f-h, b-c-f-h, -c-f-h, -h],[b-f-A, b-f-A, -f-A, 0],[-h, -h, -h, -h]])
    Qc=np.aaray([[b-c-f,0,-c-f,-c-f],[-h,-h,-h,-h],[b-f-B, 0, -f-B, -f-B], [b-f-B-h, -h, -f-B-h, -f-B-h]])
    UMc=np.array([2f, 0, 2*(f+B), 2*(f+B)])
    UMh=np.array([2f, 2f, 2f,0])
    tc+=-np.ones((12,N-1))
    tc-=-np.ones((12,N-1))
    th+=-np.ones((12,N-1))
    th-=-np.ones((12,N-1))
    fit_c=-np.ones((12,N-1))
    fit_h=-np.ones((12,N-1))
    t+_ump=-np.ones((8,N-1))
    t-_ump=-np.ones((8,N-1))
    
    fit_um=-np.ones((8,N-1))
    for j in range(N):
        fit_c[0][j]=fit(0,1,j+1,'c',Qh,Qc,N)
        fit_c[1][j]=fit(0,2,j+1,'c',Qh,Qc,N)
        fit_c[2][j]=fit(0,3,j+1,'c',Qh,Qc,N)
        fit_c[3][j]=fit(1,0,j+1,'c',Qh,Qc,N)
        fit_c[4][j]=fit(1,2,j+1,'c',Qh,Qc,N)
        fit_c[5][j]=fit(1,3,j+1,'c',Qh,Qc,N)
        fit_c[6][j]=fit(2,0,j+1,'c',Qh,Qc,N)
        fit_c[7][j]=fit(2,1,j+1,'c',Qh,Qc,N)
        fit_c[8][j]=fit(2,3,j+1,'c',Qh,Qc,N)
        fit_c[9][j]=fit(3,0,j+1,'c',Qh,Qc,N)
        fit_c[10][j]=fit(3,1,j+1,'c',Qh,Qc,N)
        fit_c[11][j]=fit(3,2,j+1,'c',Qh,Qc,N)
        fit_h[0][j]=fit(0,1,j+1,'h',Qh,Qc,N)
        fit_h[1][j]=fit(0,2,j+1,'h',Qh,Qc,N)
        fit_h[2][j]=fit(0,3,j+1,'h',Qh,Qc,N)
        fit_h[3][j]=fit(1,0,j+1,'h',Qh,Qc,N)
        fit_h[4][j]=fit(1,2,j+1,'h',Qh,Qc,N)
        fit_h[5][j]=fit(1,3,j+1,'h',Qh,Qc,N)
        fit_h[6][j]=fit(2,0,j+1,'h',Qh,Qc,N)
        fit_h[7][j]=fit(2,1,j+1,'h',Qh,Qc,N)
        fit_h[8][j]=fit(2,3,j+1,'h',Qh,Qc,N)
        fit_h[9][j]=fit(3,0,j+1,'h',Qh,Qc,N)
        fit_h[10][j]=fit(3,1,j+1,'h',Qh,Qc,N)
        fit_h[11][j]=fit(3,2,j+1,'h',Qh,Qc,N)
        
        fit_um[0][j]=fit_umpires(0,'c',j+1,N,UMc,UMh)
        fit_um[1][j]=fit_umpires(1,'c',j+1,N,UMc,UMh)
        fit_um[2][j]=fit_umpires(2,'c',j+1,N,UMc,UMh)
        fit_um[3][j]=fit_umpires(3,'c',j+1,N,UMc,UMh)
        fit_um[4][j]=fit_umpires(0,'h',j+1,N,UMc,UMh)
        fit_um[5][j]=fit_umpires(1,'h',j+1,N,UMc,UMh)
        fit_um[6][j]=fit_umpires(2,'h',j+1,N,UMc,UMh)
        fit_um[7][j]=fit_umpires(3,'h',j+1,N,UMc,UMh)
    for j in range(N):
        
        tc+[0][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[0][j]-fit_c[3][N-j-1])))
        tc+[1][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[1][j]-fit_c[6][N-j-1])))
        tc+[2][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[2][j]-fit_c[9][N-j-1])))
        tc+[3][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[3][j]-fit_c[0][N-j-1])))
        tc+[4][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[4][j]-fit_c[7][N-j-1])))
        tc+[5][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[5][j]-fit_c[10][N-j-1])))
        tc+[6][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[6][j]-fit_c[1][N-j-1])))
        tc+[7][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[7][j]-fit_c[4][N-j-1])))
        tc+[8][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[8][j]-fit_c[11][N-j-1])))
        tc+[9][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[9][j]-fit_c[2][N-j-1])))
        tc+[10][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[10][j]-fit_c[5][N-j-1])))
        tc+[11][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[11][j]-fit_c[8][N-j-1])))
        tc-[0][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[0][j]-fit_c[3][N-j-1])))
        tc-[1][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[1][j]-fit_c[6][N-j-1])))
        tc-[2][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[2][j]-fit_c[9][N-j-1])))
        tc-[3][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[3][j]-fit_c[0][N-j-1])))
        tc-[4][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[4][j]-fit_c[7][N-j-1])))
        tc-[5][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[5][j]-fit_c[10][N-j-1])))
        tc-[6][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[6][j]-fit_c[1][N-j-1])))
        tc-[7][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[7][j]-fit_c[4][N-j-1])))
        tc-[8][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[8][j]-fit_c[11][N-j-1])))
        tc-[9][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[9][j]-fit_c[2][N-j-1])))
        tc-[10][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[10][j]-fit_c[5][N-j-1])))
        tc-[11][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[11][j]-fit_c[8][N-j-1])))
        
        th+[0][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[0][j]-fit_c[3][N-j-1])))
        th+[1][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[1][j]-fit_c[6][N-j-1])))
        th+[2][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[2][j]-fit_c[9][N-j-1])))
        th+[3][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[3][j]-fit_c[0][N-j-1])))
        th+[4][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[4][j]-fit_c[7][N-j-1])))
        th+[5][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[5][j]-fit_c[10][N-j-1])))
        th+[6][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[6][j]-fit_c[1][N-j-1])))
        th+[7][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[7][j]-fit_c[4][N-j-1])))
        th+[8][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[8][j]-fit_c[11][N-j-1])))
        th+[9][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[9][j]-fit_c[2][N-j-1])))
        th+[10][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[10][j]-fit_c[5][N-j-1])))
        th+[11][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_c[11][j]-fit_c[8][N-j-1])))
        th-[0][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[0][j]-fit_c[3][N-j-1])))
        th-[1][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[1][j]-fit_c[6][N-j-1])))
        th-[2][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[2][j]-fit_c[9][N-j-1])))
        th-[3][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[3][j]-fit_c[0][N-j-1])))
        th-[4][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[4][j]-fit_c[7][N-j-1])))
        th-[5][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[5][j]-fit_c[10][N-j-1])))
        th-[6][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[6][j]-fit_c[1][N-j-1])))
        th-[7][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[7][j]-fit_c[4][N-j-1])))
        th-[8][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[8][j]-fit_c[11][N-j-1])))
        th-[9][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[9][j]-fit_c[2][N-j-1])))
        th-[10][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[10][j]-fit_c[5][N-j-1])))
        th-[11][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_c[11][j]-fit_c[8][N-j-1])))
        
        t+_ump[0][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_um[0][j]-fit_c[4][N-j-1])))
        t+_ump[1][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_um[1][j]-fit_c[5][N-j-1])))
        t+_ump[2][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_um[2][j]-fit_c[6][N-j-1])))
        t+_ump[3][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_um[3][j]-fit_c[7][N-j-1])))
        t+_ump[4][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_um[4][j]-fit_c[0][N-j-1])))
        t+_ump[5][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_um[5][j]-fit_c[1][N-j-1])))
        t+_ump[6][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_um[6][j]-fit_c[2][N-j-1])))
        t+_ump[7][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(-beta*(fit_um[7][j]-fit_c[3][N-j-1])))
        t-_ump[0][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_um[0][j]-fit_c[4][N-j-1])))
        t-_ump[1][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_um[1][j]-fit_c[5][N-j-1])))
        t-_ump[2][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_um[2][j]-fit_c[6][N-j-1])))
        t-_ump[3][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_um[3][j]-fit_c[7][N-j-1])))
        t-_ump[4][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_um[4][j]-fit_c[0][N-j-1])))
        t-_ump[5][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_um[5][j]-fit_c[1][N-j-1])))
        t-_ump[6][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_um[6][j]-fit_c[2][N-j-1])))
        t-_ump[7][j]=((j+1)/N)*(N-(j+1)/(N-1))*1/(np.exp(beta*(fit_um[7][j]-fit_c[3][N-j-1])))
        
    matrix=np.zeros((8,8))
    
    for a in range(8):
        for b in range(8):
            if 0<a<4 and 0<b<4:
                
                
                
def prob_fix_c(s1,s2):
    for i in range(1,N-1):
        for j in range(1,i):
            prod=np.prod(th-[])
        
        
       
        