#include<stdio.h>

int getmaxcol(int);

int index1=0,num;
int a[15][15],tran[15][15],original[15][15];

int main(int argc, char **argv)
 {
     int n=14,i,j,max,out[15],min,arrival[15],required[15],slack[15];
     FILE *fp;
     char nodes[] = {'G','I','A','B','D','H','K','J','C','L','E','M','F'};
    
     num=n;

     fp=fopen("inputs.txt","r");

     for(i=0;i<n;i++)
	 {
      for(j=0;j<n;j++)
	   {
      	  fscanf(fp,"%d",&a[i][j]);
          original[i][j]=a[i][j];
       }
	 }

     fclose(fp);
     
     /* Find the output nodes */
     
     for(i=0;i<n;i++)
      out[i]=0;
      
     for(i=0;i<n;i++)
     {
      for(j=0;j<n;j++)
       {
        if(a[i][j] > 0)
        break;
        
        if(j == n-1)
         out[i]=1;
       }
     }
     
    
     for(i=0;i<n;i++)
      {
        max=getmaxcol(i);
        for(j=0;j<n;j++)
         if(a[i][j] !=0 && (a[i][j]+max) > a[i][j])
           a[i][j]=(a[i][j]+max);
      }
      
    /* Find the transpose here */
     
     max=0;
     
     for(i=0;i<n;i++)
     {
        for(j=0;j<n;j++)
         if(a[i][j] > max)
         max=a[i][j];
     }
     
     for(i=1;i<n;i++)
      {
         for(j=1;j<n;j++)
          if(original[j][i] != 0)
            tran[i-1][j-1]=original[j][i];
          else
            tran[i-1][j-1]=10000;
      }
      
     for(j=0;j<n-1;j++)
     {
      if(out[j+1] != 1)
      tran[n-1][j]=10000;
      else
      tran[n-1][j]=max;
      
      tran[j][n-1]=10000;
     }
     
     tran[n-1][n-1]=10000;
     
       
    /* Find the required time */
    
     for(i=n-2;i>=0;i--)
      {
        min=getmincol(i);
        for(j=n-1;j>=0;j--)
         if(tran[i][j] !=10000)
           tran[i][j]=min-tran[i][j];
      }
      
      
    /* Print arrival, required, slack here */
    
    max=0;
    min=10000;
    
    for(i=1;i<n;i++)
     {
         for(j=0;j<n;j++)
         {
            if(a[j][i] > max)
            max=a[j][i];
         }
         
         arrival[i-1]=max;
         max=0;
     }
     
     for(i=0;i<n-1;i++)
     {
        for(j=0;j<n;j++)
         {
          if(tran[j][i] < min)
            min=tran[j][i];
         }
         
         required[i]=min;
         min=10000;
     }

	 fp=fopen("outputs.txt","w");
     fprintf(fp,"Nodes\t\tArrival\t\tRequired\tSlack\n");
     for(i=0;i<n-1;i++)
     {
       slack[i]=required[i]-arrival[i];
       fprintf(fp,"%c\t\t%d\t\t%d\t\t%d\n",nodes[i],arrival[i],required[i],slack[i]);
     }
	 fclose(fp);
 }
 
 int getmaxcol(int colnum)
  {
    int i,max;
    
     max=a[0][colnum];
    for(i=1;i<num;i++)
          if(a[i][colnum] > max)
          max = a[i][colnum];
        
     return max;
  }
  
  int getmincol(int colnum)
  {
    int i,min;
    
    min=tran[0][colnum];
    for(i=1;i<num;i++)
          if(tran[i][colnum] < min)
          min = tran[i][colnum];
        
     return min;
  }
  
