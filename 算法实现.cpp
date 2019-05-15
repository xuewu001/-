#include<stdio.h>
#include<stdlib.h>
int main()
{
    int num[1000];//货品标号对应的第几种物品
    int I[5][3]={0};//购买的物品标号，个数，单价
    int O[99][12]={0};//优惠方案（种类，商品标号及个数，总价）
    int C,K,P,B,S;
    //C商品的编码
    //K购买该种商品的数量
    //P该种商品的正常单价
    //B所购商品种类数
    //S优惠商品组合数
    int i[5],j[5];
    int m,n,x,y,z;
    int min;
    int work[6][6][6][6][6];
    FILE *fp;
    fp=fopen("input.txt","r");
    fscanf(fp,"%d",&B);
    for(m=0;m<B;m++)
    {
        fscanf(fp,"%d%d%d",&C,&K,&P);
        I[m][0]=C;
        I[m][1]=K;
        I[m][2]=P;
        num[C]=m;
    } 
    fclose(fp);
    fp=fopen("offer.txt","r");
    fscanf(fp,"%d",&S);
    for(m=0;m<S;m++)
    {
        fscanf(fp,"%d",&y);                //一个组合所需物品数量
        O[m][0]=y;
        for(n=1;n<=2*y;n++)
        {
            fscanf(fp,"%d",&x);
            if(n%2==1)
            {
                O[m][n]=num[x];
            }
            else
            O[m][n]=x;
        }
        fscanf(fp,"%d",&O[m][n]);
    }
    
    
    work[0][0][0][0][0]=0;
    
    for(i[0]=0;i[0]<=I[0][1];i[0]++)          //把所有商品 个数情况遍历一遍
    {
        for(i[1]=0;i[1]<=I[1][1];i[1]++)
        {
            for(i[2]=0;i[2]<=I[2][1];i[2]++)
            {
                for(i[3]=0;i[3]<=I[3][1];i[3]++)
                {
                    for(i[4]=0;i[4]<=I[4][1];i[4]++)
                    {
                        if(i[0]==0&&i[1]==0&&i[2]==0&&i[3]==0&&i[4]==0)
                        continue;
                        else
                        {
							work[i[0]][i[1]][i[2]][i[3]][i[4]]=1000000;
                            min=i[0]*I[0][2]+i[1]*I[1][2]+i[2]*I[2][2]+
                                i[3]*I[3][2]+i[4]*I[4][2];
                            for(m=0;m<S;m++)
                            {
                                for(n=0;n<5;n++)
                                j[n]=i[n];
 
                                for(n=1;n<=2*O[m][0];n=n+2)
                                {
                                    if(i[O[m][n]]-O[m][n+1]<0)
                                    j[O[m][n]]=0;
                                    else 
                                    j[O[m][n]]=i[O[m][n]]-O[m][n+1];
                                }
 
 
                                if(work[j[0]][j[1]][j[2]][j[3]][j[4]]+O[m][n]<min)
									 min=work[j[0]][j[1]][j[2]][j[3]][j[4]]+O[m][n];
                            }
                            work[i[0]][i[1]][i[2]][i[3]][i[4]]=min;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n",work[I[0][1]][I[1][1]][I[2][1]][I[3][1]][I[4][1]]);
    return 0;
}
