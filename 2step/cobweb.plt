
#-------------------------------------------------------------------------------
# ループ処理
#-------------------------------------------------------------------------------
if(exist("n")==0 || n<0) n = n0  # ループ変数の初期化

#-------------------------------------------------------------------------------

set zrange[n*0.01:n*0.01+0.01]
set view 0,0,1,1
 
#-------------------------------------------------------------------------------



# プロット
#-------------------------------------------------------------------------------
splot "sundT6.txt"  u 4:5:1   # n番目のデータのプロット

#-------------------------------------------------------------------------------
# ループ処理
#-------------------------------------------------------------------------------
n = n + dn            # ループ変数の増加
if ( n < n1 ) reread  # ループの評価
undefine n            # ループ変数の削除