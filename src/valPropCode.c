#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "parser.h"
#include "valPropHeader.h"

int counter[20];

typedef struct state_pair
{
  int x;    
  int y;   
}sp;   

typedef struct mem MEMB;
struct mem
{
  NC * term1;
  NC* term2;
  MEMB *next; 
};	


typedef struct simulationtab
{
  int state_id1;
  int state_id2;
  MEMB *member;
}SMT_TAB ;

typedef struct entriespair
{
  int x;//source
  int y[5];//target
  int ch;
}EP;
FSMD *M0, *M1;
extern void callParser( char* );
boolean flagVar_List;



void createnode(FSMD *M0,int i)
{
   TRANSITION_ST  *temp;
   temp=M0->states[i].translist;
   
   char *a1,*a2;
   int l,s;
   char *m1,*m2,*m3,*m4,*m5,*m6,*condition;
   a1=(char*)malloc(100);
   m1=(char*)malloc(100);
   m2=(char*)malloc(100);
   m3=(char*)malloc(100);
   m4=(char*)malloc(100);
   m5=(char*)malloc(100);
   m6=(char*)malloc(100);
   condition=(char*)malloc(100);
   NC *p8;
   
   while(temp!=NULL)
   {
     memset(condition,0,sizeof(condition));
     condition=write_lists1(temp->condition,condition);
     char *str1;
     str1=strstr(condition,"AND");
     if(str1!=NULL)
     {
	a1=strtok(condition,"AND");
        
	if(strchr(a1,'=')!=NULL)
	{
	 
          if(strchr(a1,'<')!=NULL)
          {
            m4=">";
            strcat(m1,"!");//!
            m2=strtok(a1,"+");
            m2++;
            m2++;
            if(strchr(m2,'-')!=NULL)
            {
	       m2++;
	       m3=strtok(NULL,"*");
	       m5=strtok(NULL,"<");
	       strcat(m1,m5);//n1
	       strcat(m1,m4);//>
	       strcat(m1,m2);//10
	    }
	    else
	    {
	       m3=strtok(NULL,"*");
	       m5=strtok(NULL,"<");
	       strcat(m1,m5);//n1
	       strcat(m1,m4);//>
	       if(strchr(m2,'0')!=NULL)
	          strcat(m1,m2);
               else
	       {	
		  strcat(m1,"-");
		  strcat(m1,m2);//10
		}
	     }	
	     
             l=0;
             s=0;
	     memset(m6,0,sizeof(m6));
             while(m1[l]!='\0')
             {
		if(m1[l]!=' ')
	              m6[s++]=m1[l];
		l++;
	     }
	     
	     p8=parsecondition(m6,p8);
	     
           }
	   else
           {
              m4="<";
              strcat(m1,"!");//!
              m2=strtok(a1,"+");
              m2++;
              m2++;
              if(strchr(m2,'-')!=NULL)
              {
		 m2++;
		 printf("\n hii2");
		 m3=strtok(NULL,"*");
		 m5=strtok(NULL,">");
		 strcat(m1,m5);//n1
		 strcat(m1,m4);//>
		 strcat(m1,m2);//10
	       }
	       else
	       {
		 m3=strtok(NULL,"*");
		 m5=strtok(NULL,">");
		 strcat(m1,m5);//n1
		 strcat(m1,m4);//>	
		 if(strchr(m2,'0')!=NULL)
		    strcat(m1,m2);
		 else
		 {												
		    strcat(m1,"-");
		    strcat(m1,m2);//10
		 }
		}
		l=0;
        	s=0;
		memset(m6,0,sizeof(m6));
        	while(m1[l]!='\0')
        	{
		   if(m1[l]!=' ')
		          m6[s++]=m1[l];
		   l++;
	        }
		p8=parsecondition(m6,p8);
	        
               }
	      }
	      else
	      {
                
        	a1=strtok(condition,"AND");
               
        	if(strchr(a1,'<')!=NULL)
        	{
        	   m4="<";
        	   
        	   m2=strtok(a1,"+");
        	   m2++;
        	   m2++;
        	   if(strchr(m2,'-')!=NULL)
        	   {
                      m2++;
		      m3=strtok(NULL,"*");
		      m5=strtok(NULL,">");
		      strcat(m1,m5);//n1
		      strcat(m1,m4);//>
		      strcat(m1,m2);//10
		   }
		   else
		   {
		     m3=strtok(NULL,"*");
		     m5=strtok(NULL,">");
		     strcat(m1,m5);//n1
		     strcat(m1,m4);//>	
		     if(strchr(m2,'0')!=NULL)
			 strcat(m1,m2);
		     else
		     {	
			strcat(m1,"-");
			strcat(m1,m2);//10
		     }
		    }
		    l=0;
		    s=0;
                    memset(m6,0,sizeof(m6));
        	    while(m1[l]!='\0')
        	    {
		      if(m1[l]!=' ')
			  m6[s++]=m1[l];
		      l++;
		    }
		    
		    p8=parsecondition(m6,p8);
		    
        	  }
        	  else
        	  {
        	    m4=">";
        	    
                    m2=strtok(a1,"+");
        	    m2++;
        	    m2++;
        	    if(strchr(m2,'-')!=NULL)
        	    {
		      m2++;
		      
		      m3=strtok(NULL,"*");
		      m5=strtok(NULL,">");
		      strcat(m1,m5);//n1
		      strcat(m1,m4);//>
		      strcat(m1,m2);//10
		    }
		    else
		    {
		       
		       m3=strtok(NULL,"*");
		       m5=strtok(NULL,">");
		       strcat(m1,m5);//n1
		       strcat(m1,m4);//>	
		       if(strchr(m2,'0')!=NULL)
			  strcat(m1,m2);
		      else
		      {	
	                strcat(m1,"-");
			strcat(m1,m2);//10
		      }
		    }
		    l=0;
        	    s=0;
		    memset(m6,0,sizeof(m6));
        	    while(m1[l]!='\0')
        	    {
		      if(m1[l]!=' ')
	                 m6[s++]=m1[l];
		      l++;
		    }
		    
		    p8=parsecondition(m6,p8);
		   
        	  }//outer else
        	 }//outer else
		 break;
	       }//if(str1!=NULL)
	       temp=temp->next;
	     }//while
	        int n0,j;
		char name[100]="\0",name1[10];
		strcat(name,"q00");
		sprintf(name1,"%d",M0->numstates);
		strcat(name,name1);
		
		n0=create_state(name,M0,M0->numstates);
					    					
		M0->numstates++;
		strcpy(M0->states[M0->numstates-1].state_id,name);
		M0->states[M0->numstates-1].numtrans=2;
		
		M0->states[M0->numstates-1].node_type=4;
		
		TRANSITION_ST * trans1,* trans2, *trans3,*temp3;
		trans1=(TRANSITION_ST *) malloc (sizeof(TRANSITION_ST));
		trans3=(TRANSITION_ST *) malloc (sizeof(TRANSITION_ST));
		
		temp3=M0->states[i].translist;
		int count=0;
		while(temp3->next!=NULL)
		     temp3=temp3->next;
		trans1->outtrans=n0;
	        trans1->condition=p8;
		trans1->action[0].lhs=0;
		trans1->action[0].rhs=NULL;
		trans1->next=NULL;
		temp3->next=trans1;
		temp3=M0->states[i].translist;
		temp3=temp3->next;
                
		M0->states[M0->numstates-1].translist=(TRANSITION_ST *) malloc (sizeof(TRANSITION_ST));
		trans2=M0->states[M0->numstates-1].translist;
		trans2->outtrans=temp3->outtrans;
		trans2->next=trans3;
		temp3=temp3->next;
		trans2->next->outtrans=temp3->outtrans;
		TRANSITION_ST * tem;
		temp3=M0->states[i].translist;
		temp3=temp3->next;
		tem=M0->states[M0->numstates-1].translist;
		tem->action[0]=temp3->action[0];
		tem->action[1]=temp3->action[1];
		temp3=temp3->next;
		tem=tem->next;
		tem->action[0]=temp3->action[0];
		tem->action[1]=temp3->action[1];
		char * condition1,*str1;
                condition1=(char*)malloc(100);
		temp3=M0 ->states[i].translist;
		tem=M0->states[M0->numstates-1].translist;
		M0->states[M0->numstates-1].numtrans=2;
                
		while(temp3!=NULL)
		{		
		   memset(condition,0,sizeof(condition));
                   memset(condition1,0,sizeof(condition1));
		   memset(m1,0,sizeof(m1));
                   condition = write_lists1(temp3->condition,condition);
                   str1=strstr(condition,"AND");
        	   if(str1!=NULL)
        	   {
        	      condition1=strtok(condition,"AND");
                      condition1=strtok(NULL,"AND");
                     
        	      if(strchr(condition1,'=')!=NULL)
        	      {
        		 if(strchr(condition1,'<')!=NULL)
        		 {
        		    m4=">";
        		    strcat(m1,"!");//!
        		    m2=strtok(condition1,"+");
	                    m2++;
        		    m2++;
			    if(strchr(m2,'-')!=NULL)
			    {
			      m2++;
			      m2++;
			      m2++;
			      m3=strtok(NULL,"*");
			      m5=strtok(NULL,"<");
			      strcat(m1,m5);//n1
			      strcat(m1,m4);//>
			      strcat(m1,m2);//10
			    }
			    else
			    {
			       m3=strtok(NULL,"*");
			       m5=strtok(NULL,"<");
			       strcat(m1,m5);//n1
			       strcat(m1,m4);//>
			       if(strchr(m2,'0')!=NULL)
				    strcat(m1,m2);
			       else
			       {	
				  strcat(m1,"-");
				  strcat(m1,m2);//10
			       }
			     }
			     l=0;
        	             s=0;
			     memset(m6,0,sizeof(m6));
        		     while(m1[l]!='\0')
        		     {
				if(m1[l]!=' ')
				  m6[s++]=m1[l];
			        l++;
			     }
			     p8=parsecondition(m6,p8);
			   }//if(strchr(condition,'<')!=NULL)
        		   else
                           {
        	              m4="<";
        		      strcat(m1,"!");//!
        		      m2=strtok(condition1,"+");
        		      m2++;
        		      m2++;
        		      if(strchr(m2,'-')!=NULL)
        		      {
			         m2++;
				 m2++;
				 printf("\n hii2");
				 m3=strtok(NULL,"*");
				 m5=strtok(NULL,">");
				 strcat(m1,m5);//n1
				 strcat(m1,m4);//>
				 strcat(m1,m2);//10
			       }
			       else
			       {
				 
				  m3=strtok(NULL,"*");
				  m5=strtok(NULL,">");
				  strcat(m1,m5);//n1
				  strcat(m1,m4);//>	
				  if(strchr(m2,'0')!=NULL)
				     strcat(m1,m2);
				  else
				  {	
				     strcat(m1,"-");
				     strcat(m1,m2);//10
				  }
			        }
			        l=0;
        		        s=0;
				memset(m6,0,sizeof(m6));
        			while(m1[l]!='\0')
        			{
				   if(m1[l]!=' ')
				      m6[s++]=m1[l];
				   l++;
				}
				p8=parsecondition(m6,p8);
				
        		      }
        		    }
        		    else
        		    {
                               
        		       if(strchr(condition1,'<')!=NULL)
        		       {
        			  m4="<";
        			  m2=strtok(condition1,"+");
        			  m2++;
        			  m2++;
        			  if(strchr(m2,'-')!=NULL)
        			  {
				     m2++;
				     m2++;
				    
				     m3=strtok(NULL,"*");
				     m5=strtok(NULL,">");
				     strcat(m1,m5);//n1
				     strcat(m1,m4);//>
				     strcat(m1,m2);//10
				   }
				   else
				   {
				     
				     m3=strtok(NULL,"*");
				     m5=strtok(NULL,">");
				     strcat(m1,m5);//n1
				     strcat(m1,m4);//>	
				     if(strchr(m2,'0')!=NULL)
				         strcat(m1,m2);
				     else
				     {	
					strcat(m1,"-");
					strcat(m1,m2);//10
				     }
				   }
				   l=0;
        			   s=0;
				   memset(m6,0,sizeof(m6));
        			   while(m1[l]!='\0')
        			   {
				     if(m1[l]!=' ')
					m6[s++]=m1[l];
				     l++;
				   }
				}
        			else
        			{
        			  m4=">";
        			  
        			  m2=strtok(condition1,"+");
        			 
        			  m2++;
        		          m2++;
        			  
        			  if(strchr(m2,'-')!=NULL)
        			  {
                                    m2++;
				    m2++;
				    m2++;
				    
				    m3=strtok(NULL,"*");
				    m5=strtok(NULL,">");
				    strcat(m1,m5);//n1
				    
				    strcat(m1,m4);//>
				    
				    strcat(m1,m2);//10
				   
				  }
				  else
                                  {
		                   
				    m3=strtok(NULL,"*");
				    m5=strtok(NULL,">");
				    strcat(m1,m5);//n1
				    strcat(m1,m4);//>	
				    if(strchr(m2,'0')!=NULL)
				      strcat(m1,m2);
				    else
			            {	
				      strcat(m1,"-");
				      strcat(m1,m2);//10
				    }
				  }
			          l=0;
        			  s=0;
        			  while(m1[l]!='\0')
        			  {
				    if(m1[l]!=' ')
				      m6[s++]=m1[l];
			            l++;
                                  }
				  m6[s]='\0';
				  
				}
        		      }
                              
        		      p8=parsecondition(m6,p8);
			      
			      tem->condition=p8;
			      tem=tem->next;
			    }//if(str1!=NULL)
			    temp3=temp3->next;
			  }
			  temp3=M0->states[i].translist;
			  TRANSITION_ST *temp4;
			  temp4=temp3;
			  while(temp3->next!=NULL)
			    temp3=temp3->next;
			  temp4->next=temp3;
                          
			}

void  mark_states_of_interest(FSMD *M0, FSMD *M1, char *inputch, char *outputch)
{
   char *sym_value,*str,*str1;
   int l,s,i,j,k;
   TRANSITION_ST *temp;
   NC *p,*p1,*p2,*p3,*p4,*p5,*p6,*p7,*p8;
   char * condition,*c1,*c2;
   char *c3,*c4,*c5;
   condition=(char*)malloc(1000);
   char op3[20],op,op1[20]="true";
   op3[0]='\0';
   op='\0';
   str=(char*)malloc(100*sizeof(char));
   sym_value = (char *) malloc (100*sizeof (char));
   p=create_expr(inputch,op,op3);
   p3=create_expr(op1,op,op3);
   //Initialising interested of all states as zero.
   for(i=0;i<M0->numstates;i++)
   {
     for(j=0;j<5;j++)
   	M0->states[i].interested[j]=0;
   }
   for(i=0;i<M1->numstates;i++)
   {
     for(j=0;j<5;j++)
   	M1->states[i].interested[j]=0;
   }
  
   for(i=0;i<M1->numstates;i++)
   {
      if(M1->states[i].interested[0]==0)
   	j=0;
     else
        j=1;
     //Making initial state as interested.
     if(M1->states[i].node_type==0)
   	   M1->states[i].interested[j++]=1;
     //Making branching node as interested.
     if(M1->states[i].numtrans>1)
   	  M1->states[i].interested[j++]=2;
     //making states before writing into output as interested.
     temp=M1->states[i].translist;
     
     while(temp!=NULL) 
     {
       k=0;
       while( temp->action[k].rhs != NULL) 
       {
	  symbol_for_index( temp->action[k].lhs, sym_value );
	  if(strcmp(sym_value,outputch)==0)
	  {
	      M1->states[i].interested[j++]=4;
	      p5=temp->action[k].rhs;
	  }
	  k++;
	}
	temp=temp->next;
      }
     //making states after reading from input as interested.
     temp=M1->states[i].translist;
     
     while(temp!=NULL) 
     {
        l=0;
	while( temp->action[l].rhs != NULL)
	{
	     if(compare_trees(p,temp->action[l].rhs))
	     {
		symbol_for_index(temp->action[l].lhs,sym_value);
		p2=create_expr(sym_value,op,op3);
		
	        M1->states[temp->outtrans].interested[0]=3;
	     }
	     l++;
	 }
	 temp=temp->next;
       }
     }
        
     for(i=0;i<M0->numstates;i++)
     {
       if(M0->states[i].interested[0]==0)
           j=0;
       else
            j=1;
       if(M0->states[i].node_type==0)//initial state
   	     M0->states[i].interested[j++]=1;
       if(M0->states[i].numtrans>1)
   	     M0->states[i].interested[j++]=2;
      
       temp=M0->states[i].translist;
       while(temp!=NULL) 
       {
          k=0;
          while(temp->action[k].rhs != NULL) 
          {
	     symbol_for_index(temp->action[k].lhs, sym_value );
	     if(strcmp(sym_value,outputch)==0)
	     {
	        p4=temp->action[k].rhs;
	        M0->states[i].interested[j++]=4;
	      }
	      k++;
          }
          temp=temp->next;
         }
		
   	temp=M0->states[i].translist;
   	while(temp!=NULL) 
   	{
	   l=0;
	   while( temp->action[l].rhs != NULL ) 
	   {
	      if(compare_trees(p,temp->action[l].rhs))
	      {
		 M0->states[temp->outtrans].interested[0]=3;
	         symbol_for_index(temp->action[l].lhs,sym_value);
		 p1=create_expr(sym_value,op,op3);
	      }
	      l++;
            }
	    temp=temp->next;
          }
   	}
      }



int srch(SMT_TAB entries[10], int x, int y, int count)
{
  int i;
  for(i=0;i<count;i++)
  {
    if(entries[i].state_id1==x && entries[i].state_id2==y)
      break;
  }
  return i;
} 

void insert_element(int *front,int *rear,int x1, int y1, sp s[10])
{
  if((*front)==0&&(*rear)==9)
    printf("\n queue overflow occurs");
  else if((*front)==-1&&(*rear)==-1)
  {
    *front=0;
    *rear=0;
    s[(*rear)].x=x1;
    s[(*rear)].y=y1;
  }
  else if((*rear)==9&&(*front)!=0)
  {
    (*rear)=0;
    s[(*rear)].x=x1;
    s[(*rear)].y=y1;
  }
  else
  {
    (*rear)++;
    s[(*rear)].x=x1;
    s[(*rear)].y=y1;
   }
}
 
sp delete_element(int *front, int *rear, sp s[10])
{
  sp element;
  if((*front)==-1)
  {
    element.x = -999;
    element.y=-999;
    return element;
  }
  element.x=s[(*front)].x;
  element.y=s[(*front)].y;
  if((*front)==(*rear))
    (*front)=(*rear)=-1;
  else
  {
    if((*front)==9)
      (*front)=0;
    else
      (*front)++;
    
  }
  return element;
}


void push(TRANSITION_ST *arr[10], TRANSITION_ST *temp, int *top)
{
  if(*top==10)
    return;
  else
    arr[++(*top)]=temp;
}

TRANSITION_ST* pop(TRANSITION_ST *arr[10],int *top)
{
   if(*top==-1)
     return NULL;
   TRANSITION_ST* tm;
   tm=arr[(*top)];
   return(arr[(*top)--]);
}
char s[50];
int top3= -1;

void push1(char data)
{
  s[++top3] = data;
}

char pop1()
{
  return s[top3--];
}

int stack_empty()
{
  if(top3 == -1)
    return 1;
  else
    return 0;
}

int precstack(char elem)
{
  switch(elem)
  {
    case ')':
      return 1;
    case '+':
    case '-':
      return 3;
    case '*':
    case '/':
      return 5;
    case '^':
      return 7;
  }
}

int precinput(char elem)
{
  switch(elem)
  {
    case '(':
      return 1;
    case '+':
    case '-':
      return 4;
    case '*':
    case '/':
      return 6;
    case '^':
      return 8;
  }
}

void strreverse(char s[])
{
  int i, len = 0;
  char temp;
  int tlen=0;
  tlen = strlen(s);
  len = tlen-1;
  for(i=0;i<tlen/2;i++)
  {
    temp = s[i];
    s[i] = s[len];
    s[len--] = temp;
  }
}

char *i2p(char infx[])
{
  char *prfx, ch, elem;
  prfx=(char*)malloc(100);
  int i = 0, k = 0;
  strreverse(infx);
  while((ch=infx[i++]) != '\0')
  {
    if( ch == ')') 
      push1(ch);
    else if(isalnum(ch))
      prfx[k++]=ch;
    else if( ch == '(')
    {
      while( s[top3] != ')')
        prfx[k++]=pop1();
      elem=pop1();
    }
    else
    {
      while(stack_empty() != 1)
      {
        if(precinput(ch) <= precstack(s[top3]))
          prfx[k++]=pop1();
        else
          break;
      }
      push1(ch);
    }
  }
  while( stack_empty() != 1)
    prfx[k++]=pop1();
  prfx[k]='\0';
  strreverse(prfx);
  strreverse(infx);
  return prfx;
}

char* modified(char cond[100])
{
  int len;
  char cond1[100];
  char *cond2;
  cond2=(char*)malloc(1000);
  len=strlen(cond);
  int i=0,j=0;
  while(cond[i]!='\0')
  {
    if(cond[i]!=' ')
      cond1[j++]=cond[i];
    i++;
  }
  cond2=i2p(cond1);
  return cond2;
}

int res(int x, int y,SMT_TAB entries[10])
{
  int i=0;
  for(i=0;i<10;i++)
  {
    if(entries[i].state_id1==x&&entries[i].state_id2==y)
      return 0;
  }
  return 1;
}

        	
char *fun(char z[100])
{
  int i2=0,i3=0;
  char cond3[100],cond4[100];
  while(z[i2]!='\0')
  {
    cond3[i3++]=z[i2++];
    cond3[i3++]=' ';
  }
  cond3[i3]='\0';
  i2=0;i3=0;
  int cnt=0;
  while(cond3[i2]!='\0')
  {
    if(cond3[i2]=='+'||cond3[i2]=='*')
    {
      cond4[i3++]='(';
      cond4[i3++]=cond3[i2++];
      ++cnt;
    }
    else
      cond4[i3++]=cond3[i2++];
  }
  while(cnt!=0)
  {
    cond4[i3++]=')';
    cnt--;
  }
  cond4[i3]='\0';
  return cond4;
}

int pairingrelatedstates(FSMD *M0,FSMD *M1,SMT_TAB entries[10],char *inputch,char *outputch)
{
  sp s[10];
  int front=-1,rear=-1;//used for implementing queue
  entries[0].state_id1=0;//intialising first related pair with state_id's of starting states.
  entries[0].state_id2=0;
  char op3[20],op,op1[20]="true";
  op3[0]='\0';
  op='\0';
  NC *p1,*p2,*p3,*p4,*p6,*p7;
  sp s1;

  int l=0;
  char * condition,*c1,*c2,*condition1,*condition2;
  condition=(char*)malloc(1000);
  condition1=(char*)malloc(1000);
  condition2=(char*)malloc(1000);
  TRANSITION_ST *temp,*temp1;
 
  insert_element(&front,&rear,0,0,s);
  s1=delete_element(&front,&rear,s);
  //printf("\n son %d \t %d\n",s1.x,s1.y);
  p1=create_expr(op1,op,op3);
  int count=0;
  char *sym_value;
  sym_value=(char*)malloc(100);
  
  p3=create_expr(inputch,op,op3);
  p4=create_expr(outputch,op,op3);
  /*****first entry completed ************/
  l2: while(s1.x!=-999&&s1.y!=-999)
  {
    
    if(M0->states[s1.x].numtrans==0&&M1->states[s1.y].numtrans==0)
	{	
          temp=M0->states[s1.x].translist;
	  temp1=M1->states[s1.y].translist;
	  l=0;
	  entries[count].state_id1=s1.x;
	  entries[count].state_id2=s1.y;
	  //M0->states[s1.x].tab=count;
	  //M1->states[s1.y].tab=count;
	  temp=M0->states[(s1.x)-1].translist;
	  temp1=M1->states[(s1.y)-1].translist;
	  while(temp->action[l].rhs!=NULL)
	  {
            if(compare_trees(p3,temp->action[l].rhs))
	    {
	      symbol_for_index(temp->action[l].lhs,sym_value);
	      p2=create_expr(sym_value,op,op3);
	      (entries[count].member)->term1=p2;
            }
	    l++;
	  }
          l=0;
	  while(temp1->action[l].rhs!=NULL)
	  {
	    if(compare_trees(p3,temp1->action[l].rhs))
	    {
	      symbol_for_index(temp1->action[l].lhs,sym_value);
	      p2=create_expr(sym_value,op,op3);
	      (entries[count++].member)->term2=p2;
            }
	    l++;
	  }
	  break;
        }//if
        if(M0->states[s1.x].numtrans==1&&M1->states[s1.y].numtrans==1)
	{
	  		
	  temp=M0->states[s1.x].translist;
	  temp1=M1->states[s1.y].translist;
         
	  if(M0->states[temp->outtrans].interested[0]!=0&&M1->states[temp1->outtrans].interested[0]!=0)
	  {
	    if(res(temp->outtrans,temp1->outtrans,entries))
	      insert_element(&front,&rear,temp->outtrans,temp1->outtrans,s);
	   }
                      
           if(M0->states[s1.x].interested[0]==1&&M1->states[s1.y].interested[0]==1)
	   {
	     entries[count].state_id1=s1.x;
	     entries[count].state_id2=s1.y;
	     //M0->states[s1.x].tab=count;
	     //M1->states[s1.y].tab=count;
	     (entries[count++].member)->term1=p1;
	   }	
           
	   else if(M0->states[s1.x].interested[0]==3&&M1->states[s1.y].interested[0]==3)
	   {
	     l=0;
	     entries[count].state_id1=s1.x;
	     entries[count].state_id2=s1.y;
	    
	     temp=M0->states[(s1.x)-1].translist;
	     temp1=M1->states[(s1.y)-1].translist;
	     write_lists(temp->action[l].rhs);
	     while(temp->action[l].rhs!=NULL)
	     {
	       if(compare_trees(p3,temp->action[l].rhs))
	       {
	         symbol_for_index(temp->action[l].lhs,sym_value);
		 p2=create_expr(sym_value,op,op3);
		 (entries[count].member)->term1=p2;
	       }
	       l++;
	     }
             l=0;
	     while(temp1->action[l].rhs!=NULL)
	     {
	       if(compare_trees(p3,temp1->action[l].rhs))
	       {
	         symbol_for_index(temp1->action[l].lhs,sym_value);
		 p2=create_expr(sym_value,op,op3);
		 (entries[count++].member)->term2=p2;
	       }
	       l++;
	     }
	   }
	   else 
	   {
	     entries[count].state_id1=s1.x;
	     entries[count].state_id2=s1.y;
	     
	     l=0;
	     while(temp->action[l].rhs!=NULL)
	     {
	       symbol_for_index(temp->action[l].lhs,sym_value);
	       p2=create_expr(sym_value,op,op3);
	       if(compare_trees(p2,p4))
	         (entries[count].member)->term1=temp->action[l].rhs;
	       l++;
	     }
	     l=0;
	     while(temp1->action[l].rhs!=NULL)
	     {
	       symbol_for_index(temp1->action[l].lhs,sym_value);
	       p2=create_expr(sym_value,op,op3);
	       if(compare_trees(p2,p4))
	         (entries[count++].member)->term2=temp1->action[l].rhs;
	       l++;
             }
	   }//else	
	 }
	 else 
         {
	   temp=M0->states[s1.x].translist;
          
	   while(temp!=NULL)
	   {
             
	     memset(condition1,0,sizeof(condition1));
	     condition1=write_lists1(temp->condition,condition1);
	    
	     if(strchr(condition1,'=')!=NULL)
	     {
	       temp1=M1->states[s1.y].translist;
	       while(temp1!=NULL)
	       {
	         condition2=write_lists1(temp1->condition,condition2);
		 if(strchr(condition2,'=')!=NULL)
		 {
		   if(M0->states[temp->outtrans].interested[0]!=0&&M1->states[temp1->outtrans].interested[0]!=0)
		   {
		     if(res(temp->outtrans,temp1->outtrans,entries))
		       insert_element(&front,&rear,temp->outtrans,temp1->outtrans,s);
		     break;
		   }
		 }//if(strchr(condition2,'=')!=NULL)	
		 temp1=temp1->next;
	       }//while(temp1!=NULL)
	     }//if(strchr(condition1,'=')!=NULL)
	     else if(strchr(condition1,'=')==NULL)
	     {
	       temp1=M1->states[s1.y].translist;
	       while(temp1!=NULL)
	       {
	         memset(condition2,0,sizeof(condition2));
		 condition2=write_lists1(temp1->condition,condition2);
		 if(strchr(condition2,'=')==NULL)
		 {
		   if(M0->states[temp->outtrans].interested[0]!=0&&M1->states[temp1->outtrans].interested[0]!=0)
		   {

		     if(res(temp->outtrans,temp1->outtrans,entries))
		       insert_element(&front,&rear,temp->outtrans,temp1->outtrans,s);
		     break;
		   }
		 }//if(strchr(condition2,'=')!=NULL)	
		 temp1=temp1->next;
	       }//while(temp1!=NULL)
	      }
              temp=temp->next;
	      }
	      entries[count].state_id1=s1.x;
	      entries[count].state_id2=s1.y;
	      temp=M0->states[s1.x].translist;
	      memset(condition1,0,sizeof(condition1));
	      condition1=write_lists1(temp->condition,condition1);
	      if(strchr(condition1,'>')!=NULL)
              {
                c1 = strtok(condition1,">");
        	c1=strtok(c1,"*");
        	c1=strtok(NULL, "*");
        	c1++;
        	p6=createVariable(c1);
        	(entries[count].member)->term1=p6;
	      }
	      else
	      {
	        c1 = strtok(condition1,"<");
        	c1=strtok(c1,"*");
        	c1=strtok(NULL, "*");
        	c1++;
        	p6=createVariable(c1);
        	(entries[count].member)->term1=p6;
              }
              temp=M1->states[s1.y].translist;
	      memset(condition1,0,sizeof(condition1));
	      condition1=write_lists1(temp->condition,condition1);
	      if(strchr(condition1,'>')!=NULL)
              {
                c1 = strtok(condition1,">");
        	c1=strtok(c1,"*");
        	c1=strtok(NULL, "*");
        	c1++;
        	p6=createVariable(c1);
        	(entries[count++].member)->term2=p6;
	      }
	      else
	      {
	        c1 = strtok(condition1,"<");
        	c1=strtok(c1,"*");
        	c1=strtok(NULL, "*");
        	c1++;
        	p6=createVariable(c1);
        	(entries[count++].member)->term2=p6;
              }
            }
                    
	    if(M0->states[s1.x].numtrans==1)
	    {
	      temp=M0->states[s1.x].translist;
	      temp1=M1->states[s1.y].translist;
	      if(M0->states[temp->outtrans].interested[0]==0&&M1->states[temp1->outtrans].interested[0]==0)
	      {
	        l3: temp=M0->states[temp->outtrans].translist;
		temp1=M1->states[temp1->outtrans].translist;
		if(temp==NULL&&temp1==NULL)
		  break;
		else if(M0->states[temp->outtrans].interested[0]==0&&M1->states[temp1->outtrans].interested[0]==0)
	        {
		  goto l3;
		}
		else
		{
		  s1.x=temp->outtrans;
		  s1.y=temp1->outtrans;
		  continue;
		}
	      }
            }
            
            s1=delete_element(&front,&rear,s);
	    
          }//while(s1.x!=-999&&s1.y!=-999)
          return count;
        }


int check(int x, int y, SMT_TAB entries[10], SMT_TAB entries1[10],int count,int ch)
{
  int k,l,m,n;
  int top=-1,top1=-1;
  TRANSITION_ST *temp,*temp1,*temp2;
  TRANSITION_ST *arr[10];
  TRANSITION_ST *arr1[10];
  k=entries[x].state_id1;//state_id of first state in the source pair.
  l=entries[x].state_id2;//state_id of second state in the source pair.
  m=entries[y].state_id1;//state_id of first state in the target pair.
  n=entries[y].state_id2;//state_id of second state in the target pair.
  char *condition1;
  condition1=(char*)malloc(1000);
 
  if(M0->states[k].numtrans==1)
  {
    temp=M0->states[k].translist;
    push(arr,temp, &top);
    while(temp->outtrans!=m)
    {
      temp=M0->states[temp->outtrans].translist;
      push(arr, temp, &top);
    }
  }

 
  if(M1->states[l].numtrans==1)
  {
    temp1=M1->states[l].translist;
    push(arr1, temp1,&top1);
    while(temp1->outtrans!=n)
    {
      temp1=M1->states[temp1->outtrans].translist;
      push(arr1, temp1,&top1);
    }
  }
  
  if(M0->states[k].numtrans==2)
  {
    
    if(ch==1)
    {
      temp=M0->states[k].translist;
      memset(condition1,0,sizeof(condition1));
      condition1=write_lists1(temp->condition,condition1);
      if(strchr(condition1,'=')!=NULL)
        temp=temp->next;
      push(arr, temp ,&top);
      while(temp->outtrans!=m)
      {
        temp=M0->states[temp->outtrans].translist;
	push(arr,temp ,&top);
      }
      temp1=M1->states[l].translist;
      memset(condition1,0,sizeof(condition1));
      condition1=write_lists1(temp1->condition,condition1);
      if(strchr(condition1,'=')!=NULL)
        temp1=temp1->next;
      push(arr1, temp1,&top1);
      while(temp1->outtrans!=n)
      {
        temp1=M1->states[temp1->outtrans].translist;
	push(arr1,temp1,&top1);
      }
    }
    else
    {
      temp=M0->states[k].translist;
      memset(condition1,0,sizeof(condition1));
      condition1=write_lists1(temp->condition,condition1);
      if(strchr(condition1,'=')==NULL)
        temp=temp->next;
      push(arr,temp,&top);
      while(temp->outtrans!=m)
      {
         temp=M0->states[temp->outtrans].translist;
	 push(arr,temp ,&top);
      }
      temp1=M1->states[l].translist;
      memset(condition1,0,sizeof(condition1));
      condition1=write_lists1(temp1->condition,condition1);
      if(strchr(condition1,'=')==NULL)
        temp1=temp1->next;
      push(arr1,temp1,&top1);
      while(temp1->outtrans!=n)
      {
        temp1=M1->states[temp1->outtrans].translist;
	push(arr1,temp1 ,&top1);
      }
    }//outer else
  }
  int c=0;NC *p1;
  MEMB *p;
  char *sym_value1;
  sym_value1=(char*)malloc(1000);
  
  while((temp=pop(arr,&top))!=NULL)
  {
    c=0;
    while(temp->action[c].rhs!=NULL)
      c++;
    c=c-1;
    p=entries1[y].member;
    while(c>=0)
    {
      while(p!=NULL)
      {
        memset(sym_value1,0,sizeof(sym_value1));
        symbol_for_index(temp->action[c].lhs,sym_value1);
        p1=createVariable(sym_value1);
        if(compare_trees(p1,p->term1))
          p->term1=temp->action[c].rhs;
        p=p->next;
      }
      c--;
    }
  }
  p=entries1[y].member;
  c=0;
  
  while((temp=pop(arr1,&top1))!=NULL)
  {
    c=0;
    while(temp->action[c].rhs!=NULL)
	c++;
    c=c-1;
    while(c>=0)
    {
      p=entries1[y].member;
      while(p!=NULL)
      {
        memset(sym_value1,0,sizeof(sym_value1));
	symbol_for_index(temp->action[c].lhs,sym_value1);
	
	p1=createVariable(sym_value1);
	if(compare_trees(p1,p->term2))
	  p->term2=temp->action[c].rhs;
	p=p->next;
      }
      c--;
    }
  }
  
  if(x==0)
  { 
    if(compare_trees((entries1[y].member)->term1,(entries1[y].member)->term2))
    {
      printf("\n there is no need to strengthen the condition at entry 0 %s %s",M0->states[k].state_id, M1->states[l].state_id);
      printf("\n the SRF at related pair %s %s in first iteration  is ",M0->states[k].state_id, M1->states[l].state_id);
      write_lists((entries[x].member)->term1);printf("\n");
      (entries1[y].member)->term1=(entries[y].member)->term1;//copying older SRFs at target pair again into copy of simulation table entries.
      (entries1[y].member)->term2=(entries[y].member)->term2;//copying older SRFs at target pair again into copy of simulation table entries.
      return 0;
    }
   
    else
    {
      printf("\n We need to strengthen the condition at entry 0 %s %s",M0->states[k].state_id, M1->states[l].state_id);
      ((entries[x].member)->next)->term1=(entries1[y].member)->term1;
      ((entries[x].member)->next)->term2=(entries1[y].member)->term2;
      printf("\n the SRF at related pair %s %s in second  iteration  is ",M0->states[k].state_id, M1->states[l].state_id);
      write_lists((entries[x].member)->term1);printf("\n");
      printf(" ^ ");
      write_lists(((entries[x].member)->next)->term1);printf(" = ");write_lists(((entries[x].member)->next)->term2);
      (entries1[y].member)->term1=(entries[y].member)->term1;//copying older SRFs at target pair again into copy of simulation table entries.
      (entries1[y].member)->term2=(entries[y].member)->term2;//copying older SRFs at target pair again into copy of simulation table entries.
      return 1;
    }
   }
  
  else 
  {
    //converting SRFs into format readable by Z3 SMT SOLVER.
    char *cond1,*cond11;
    char *cond2,*cond22;
    cond1=(char*)malloc(1000);
    cond2=(char*)malloc(1000);
    cond11=(char*)malloc(1000);
    cond22=(char*)malloc(1000);
    memset(cond1,0,sizeof(cond1));
    memset(cond2,0,sizeof(cond2));
    memset(cond11,0,sizeof(cond11));
    memset(cond22,0,sizeof(cond22));
    char *c1,*c2,*c3,*c4,*c5,*c6,*c7,*c8;
    c1=(char*)malloc(50);
    c2=(char*)malloc(50);
    c5=(char*)malloc(50);
    c6=(char*)malloc(50);
    
    cond1=write_lists1((entries[x].member)->term1,cond1);
    strcpy(c1,cond1);
    strtok(c1,"*");
    c3=strtok(NULL,"*");
    
    cond1=modified(cond1);
    
    int i2=0,i3=0,cnt=0;
    char z[100];
    strcpy(z,cond1);
    char *y1;
   
    y1=fun(z);
    char y2[100];
    strcpy(y2,y1);

    cond2=write_lists1((entries[x].member)->term2,cond2);
    strcpy(c2,cond2);
    strtok(c2,"*");
    c4=strtok(NULL,"*");
    cond2=modified(cond2);
    char *y3;
    strcpy(z,cond2);
    y3=fun(z);
    char y4[100];
    strcpy(y4,y3);
    cond11=write_lists1((entries1[y].member)->term1,cond11);
    strcpy(c5,cond11);
    strtok(c5,"*");
    c7=strtok(NULL,"*");
    cond11=modified(cond11);
    char *y5;
    strcpy(z,cond11);
    y5=fun(z);
    char y6[100];
    strcpy(y6,y5);	
    cond22=write_lists1((entries1[y].member)->term2,cond22);
    strcpy(c6,cond22);
    strtok(c6,"*");
    c8=strtok(NULL,"*");
    cond22=modified(cond22);
    char *y7;
    strcpy(z,cond22);
    y7=fun(z);
    char y8[100];
    strcpy(y8,y7);//y7=cond10
    
    if(((entries[x].member)->next)==NULL)
    {
      
      FILE *fp;
      char str1[50];
      fp=fopen("1.txt","w");
      fprintf(fp,"(declare-const");
      fprintf(fp,"%s Int)",c3);
      fprintf(fp,"\n");
      fprintf(fp,"(declare-const");
      fprintf(fp,"%s Int)",c4);
      fprintf(fp,"\n");
      if(strcmp(c3,c7)!=0)
      {
        fprintf(fp,"(declare-const");
        fprintf(fp,"%s Int)",c7);
        fprintf(fp,"\n"); 
      }
      if(strcmp(c4,c8)!=0)
      {
        fprintf(fp,"(declare-const");
        fprintf(fp,"%s Int)",c8);
        fprintf(fp,"\n");
      }
      fprintf(fp,"(assert (not (=> (= ");
      fprintf(fp,"%s%s)(= ",y2,y4);
      fprintf(fp,"%s%s))))",y6,y8);
      fprintf(fp,"\n");
      fprintf(fp,"(check-sat)");
      fclose(fp);
      char cmd[1000];
      strcpy(cmd,"/usr/bin/z3 -smt2 ");
      strcat(cmd,"1.txt");
      strcat(cmd," > ");
      strcat(cmd,"1o.txt");
      system(cmd);
      FILE *fp1;
      fp1=fopen("1o.txt","r");
      fscanf(fp1,"%s",str1);
      fclose(fp1);
      if(strcmp(str1,"unsat")==0)
      {
        printf("\n no need to strengthen the condition at entry %d %s %s",x,M0->states[k].state_id, M1->states[l].state_id);
        printf("\n SRF at %s %s in second iteration is ",M0->states[k].state_id, M1->states[l].state_id);
        write_lists((entries[x].member)->term1);printf("=");write_lists((entries[x].member)->term2);printf("\n");
	(entries1[y].member)->term1=(entries[y].member)->term1;
	(entries1[y].member)->term2=(entries[y].member)->term2;
	return 0;
      }
       
      else
      {
	MEMB m9,m10;
        (entries[x].member)->next=&m9;
        ((entries[x].member)->next)->term1=(entries1[y].member)->term1;
	((entries[x].member)->next)->term2=(entries1[y].member)->term2;
        printf("\n we need to strengthen the condition at  entry %d %s %s",x,M0->states[k].state_id, M1->states[l].state_id);
        printf("\n SRF at %s %s in second iteration is",M0->states[k].state_id, M1->states[l].state_id);
        write_lists((entries[x].member)->term1);printf("=");write_lists((entries[x].member)->term2);printf("^");
        write_lists(((entries[x].member)->next)->term1);printf("=");write_lists(((entries[x].member)->next)->term2);
        (entries1[y].member)->term1=(entries[y].member)->term1;
	(entries1[y].member)->term2=(entries[y].member)->term2;
        return 1;
     }
    }
    
    else
    {
      char *cond1n;
      char *cond2n;
      cond1n=(char*)malloc(1000);
      cond2n=(char*)malloc(1000);
      memset(cond1n,0,sizeof(cond1n));
      memset(cond2n,0,sizeof(cond2n));
      char *c1n,*c2n,*d,*c4n,*c5n,*c6n,*c7n,*c8n,*p;
      c1n=(char*)malloc(50);
      c2n=(char*)malloc(50);
      c5n=(char*)malloc(50);
      c6n=(char*)malloc(50);
     
      cond1n=write_lists1(((entries[x].member)->next)->term1,cond1n);
      strcpy(c1n,cond1n);
      strtok(c1n,"*");
      d=strtok(NULL,"*");
      cond1n=modified(cond1n);
      char *y9;
      strcpy(z,cond1n);
      y9=fun(z);
      char y10[100];
      strcpy(y10,y9);
     	
      cond2n=write_lists1(((entries[x].member)->next)->term2,cond2n);
      strcpy(c2n,cond2n);
      strtok(c2n,"*");
      c4n=strtok(NULL,"*");
      cond2n=modified(cond2n);
      char *y11;
      strcpy(z,cond2n);
      y11=fun(z);
      char y12[100];
      strcpy(y12,y11);//y12=cond6n
   
   FILE *fp;
   char str1[50];
   fp=fopen("1.txt","w");
   fprintf(fp,"(declare-const");
   fprintf(fp,"%s Int)",c3);
   fprintf(fp,"\n");
   fprintf(fp,"(declare-const");
   fprintf(fp,"%s Int)",c4);
   fprintf(fp,"\n"); 
   if(strcmp(c3,c7)!=0)
      {
        fprintf(fp,"(declare-const");
        fprintf(fp,"%s Int)",c7);
        fprintf(fp,"\n"); 
      }
      if(strcmp(c4,c8)!=0)
      {
        fprintf(fp,"(declare-const");
        fprintf(fp,"%s Int)",c8);
        fprintf(fp,"\n");
      }
      if((strcmp(d,c3)!=0)&&(strcmp(d,c7)!=0))
      { 
        fprintf(fp,"(declare-const");
        fprintf(fp,"%s Int)",d);
        fprintf(fp,"\n");
      }
      if((strcmp(c4n,c4)!=0)&&(strcmp(c4n,c8)!=0))
      {
        fprintf(fp,"(declare-const");
        fprintf(fp,"%s Int)",c4n);
        fprintf(fp,"\n");
      }
      fprintf(fp,"(assert (not (=> (and (= ");
      fprintf(fp,"%s",y2);
      fprintf(fp,"%s",y4);
      fprintf(fp,")(= ");
      fprintf(fp,"%s",y10);
      fprintf(fp,"%s",y12);
      fprintf(fp,")) (= ");
      fprintf(fp,"%s",y6);
      fprintf(fp,"%s",y8);
      fprintf(fp,"))))");
      fprintf(fp,"\n");
      fprintf(fp,"(check-sat)");
      fclose(fp);
      char cmd[1000];
      strcpy(cmd,"/usr/bin/z3 -smt2 ");
      strcat(cmd,"1.txt");
      strcat(cmd," > ");
      strcat(cmd,"1o.txt");
      system(cmd);
      FILE *fp1;
      fp1=fopen("1o.txt","r");
      fscanf(fp1,"%s",str1);
      fclose(fp1);
      /*****Purpose of this If:
      If SOLVER gives unsat means no need to strengthen the condition at source pair SRF and returns 0.
      *****/
      if(strcmp(str1,"unsat")==0)
      {
        printf("\n no need to strengthen the condition at  entry %d %s %s",x,M0->states[k].state_id, M1->states[l].state_id);
	(entries1[y].member)->term1=(entries[y].member)->term1;
	(entries1[y].member)->term2=(entries[y].member)->term2;
        ((entries1[y].member)->next)->term1=((entries[y].member)->next)->term1;
        ((entries1[y].member)->next)->term2=((entries[y].member)->next)->term2;
	return 0;
      }
      /*****Purpose of this else:
      If SOLVER gives sat means we need to strengthen the condition at source pair SRF and returns 1.
      ****/
      else
      {
        MEMB m11,m12;
        ((entries[x].member)->next)->next=&m11;
        (((entries[x].member)->next)->next)->term1=(entries1[y].member)->term1;//adding modified SRF term1 as conjunction to already exists 		source pair SRF term1.
	(((entries[x].member)->next)->next)->term2=(entries1[y].member)->term2;// adding modified SRF term3 as conjunction to already exists 		source pair SRF term2.
        
      
        printf("\n we need to strengthen the condition at  entry %d %s %s",x,M0->states[k].state_id, M1->states[l].state_id);
        printf("\n SRF at %s %s is third iteration is",M0->states[k].state_id, M1->states[l].state_id);
        write_lists((entries[x].member)->term1);printf("="); write_lists((entries[x].member)->term2);printf("^");
        write_lists(((entries[x].member)->next)->term1);printf("="); write_lists(((entries[x].member)->next)->term2);printf("^");
        write_lists((((entries[x].member)->next)->next)->term1);printf("=");write_lists((((entries[x].member)->next)->next)->term2);
        printf("\n");
	(entries1[y].member)->term1=(entries[y].member)->term1;
	(entries1[y].member)->term2=(entries[y].member)->term2;
        return 1;
        
      }
     }
   }//else
 }//check
		
		

int srch1(EP pair[10],int count,int x)
{
  int i;
  for(i=0;i<count;i++)
  {
    if(pair[i].y[0]==x)
       return pair[i].x;
  }
}

void findingfinalsrf(FSMD *M0, FSMD *M1, SMT_TAB entries[10], SMT_TAB entries1[10],EP pair[10], char *inputch, char *outputch, int count,char argv1[2][100])
{
   int flag;
    
   int i,k,l,a1,a2;
   TRANSITION_ST *temp, *temp1, *temp3, *temp4;
   char *condition1, *condition2;
   condition1=(char*)malloc(1000);
   condition2=(char*)malloc(1000);
   
   for(i=0;i<count;i++)
    pair[i].x=i;
  
  for(i=0;i<count;i++)
  {
    k=entries[pair[i].x].state_id1;//k is the state_id of the state (in FSMD M0) in the source related pair.
    l=entries[pair[i].x].state_id2;//l is the state_id of the state (in FSMD M1) in the source related pair.
    
    s1:if(M0->states[k].numtrans==0&&M1->states[l].numtrans==0)
       {
         pair[i].y[0]=-99;
	 continue;
       }
       

       if(M0->states[k].numtrans==1&&M1->states[l].numtrans==1)
       {
         temp=M0->states[k].translist;
	 temp1=M1->states[l].translist;
        
	 if(M0->states[temp->outtrans].interested[0]!=0&&M1->states[temp1->outtrans].interested[0]!=0)
	   pair[i].y[0]=srch(entries,temp->outtrans,temp1->outtrans,count);
	
         else
	 {
	   k=temp->outtrans;
	   l=temp1->outtrans;
	   goto s1;
	 }
       }
       else
       {
	 temp=M0->states[k].translist;
	 temp1=M1->states[l].translist;
	 int n=0;
        
	 while(temp!=NULL)
	 {
	   memset(condition1,0,sizeof(condition1));
	   condition1=write_lists1(temp->condition,condition1);
	   
           if(strchr(condition1,'=')!=NULL)
	   {
	     temp1=M1->states[l].translist;
	     while(temp1!=NULL)
	     {
	       memset(condition2,0,sizeof(condition2));								
	       condition2=write_lists1(temp1->condition,condition2);
	       if(strchr(condition2,'=')!=NULL)
	       {
		 temp3=temp;temp4=temp1; 
		 s5:if(M0->states[temp3->outtrans].interested[0]!=0)
		      a1=temp3->outtrans;
		    else
		    {
		      temp3=M0->states[temp3->outtrans].translist;
			if(temp3==NULL)
			  break;
			goto s5;
		    }
		    s6:if(M1->states[temp4->outtrans].interested[0]!=0)
		         a2=temp4->outtrans;
			 else
			 {
			   temp4=M0->states[temp4->outtrans].translist;
			   if(temp4==NULL)
			     break;
			   goto s6;	
			 }
			 pair[i].y[n++]=srch(entries,a1,a2,count);
			 pair[i].ch=0;
           }//if
	   temp1=temp1->next;
	 }
       }
       else
       {
         temp1=M1->states[l].translist;
         while(temp1!=NULL)
         {
	   memset(condition2,0,sizeof(condition2));
           condition2=write_lists1(temp1->condition,condition2);
           if(strchr(condition2,'=')==NULL)
	   {
	     temp3=temp;temp4=temp1;
	     s3:if(M0->states[temp3->outtrans].interested[0]!=0)	
		  a1=temp3->outtrans;
	        else
	        {
	          temp3=M0->states[temp3->outtrans].translist;
		  if(temp3==NULL)
	            break;
		  goto s3;
	        }
	      s4: if(M1->states[temp4->outtrans].interested[0]!=0)
	             a2=temp4->outtrans;
		  else
		  {
		    temp4=M0->states[temp4->outtrans].translist;
		    if(temp4==NULL)
		      break;
		    goto s4;	
		  }
		  pair[i].y[n++]=srch(entries,a1,a2,count);
		  pair[i].ch=1;
	        }//if
	        temp1=temp1->next;
	      }//while
	    }//else
            if(temp==NULL)
	      break;
	    temp=temp->next;
	  }//outerwhile
        }//outer else
      }//for loop
     
/**************************************pairing completed ********************************************************/
printf("\n *********** PAIRING OF STATES IN SIMULATION TABLE ***********\n");
for(i=0;i<count;i++)
{
  printf("%d\t %d \t%d",pair[i].x,pair[i].y[0],pair[i].y[1]);
  printf("\n");
}
i=0;
int result,tar;

for(i=0;i<count;i++)
{

  if(pair[i].y[0]==-99)
    continue;

  else if(pair[i].y[0]!=-99 && pair[i].y[1]==-99)
  {
    
    result=check(pair[i].x, pair[i].y[0],entries,entries1,count,pair[i].ch);
    
    if(result==0)
      continue;
   
    else
    {
      
      a3:tar=srch1(pair,count,pair[i].x);
      result=check(tar,pair[i].x,entries,entries1,count,pair[i].ch);
      if(result==0)
        continue;
      else
      {
        pair[i].x=tar;
	goto a3;
      }
    }
  }
  
  else 
  { 
    if(flag==1)
      result=check(pair[i].x,pair[i].y[1],entries,entries1,count,1);
    result=check(pair[i].x,pair[i].y[0],entries,entries1,count,0);
  }			
 }//for loop
}//findingfinalsrf		
		

int main( int argc, char* argv[] )
{
  //copying filenames into an arry argv1.
  char argv1[2][100];
  strcpy(argv1[0],argv[1]);
  strcpy(argv1[1],argv[2]);
  char inputch[100],outputch[100];//inputch is input channel and outputch is output channel
  int i;
  if(argc != 3)
  {
     printf("\nInadequate number of parameters provided\nExiting System\n");
     return 0;
  }
  flagVar_List = FALSE;
  outputVar0.no_of_elements = 0;
   
   callParser(argv[1]); 
  
   flagVar_List = TRUE;
   outputVar1.no_of_elements = 0;
   
   callParser(argv[2]);
   
   printf("\n enter the input channel?");
   scanf("%s",inputch);
   printf("\n enter the outputchannel?");
   scanf("%s",outputch);
  
  mark_states_of_interest(M0,M1,inputch,outputch);
  
  for(i=0;i<M0->numstates;i++)
  {
     if(M0->states[i].numtrans>2)
     {
        
        createnode(M0,i);
        // after creating newnode again marking states of interest for modified FSMD.
        mark_states_of_interest(M0,M1,inputch,outputch);
        break;
      }
  }
  
  for(i=0;i<M1->numstates;i++)
  {
    if(M1->states[i].numtrans>2)
    {		
	
	createnode(M1,i);
	// after creating newnode again marking states of interest for modified FSMD.
	mark_states_of_interest(M0,M1,inputch,outputch);
	
	break;
     }
  }
  
  // SMT_TAB is structure for simulation table entry. entries is  an array of simulation table entries . 
  SMT_TAB entries[10],entries1[10];
  //EP is a data structure for storing source and target entries.
  EP pair[10];
  int n,j,count;
  //MEMB is a data structure for storing the state relating formula for simulation table entry.
  MEMB m[10],m1[10],m2[10],m3[10],m4[10],m5[10],m6[10];
  for(i=0;i<10;i++)
     entries[i].member=&m[i];/*allocating memory for member */
  /****
  Allocating memory for terms used as SRFs for related pairs.
  *****/
  for(i=0;i<10;i++)
  {
    (entries[i].member)->next=&m1[i];
    (entries[i].member)->next=NULL;
  }
  for(i=0;i<10;i++)
      entries1[i].member=&m3[i];
  for(i=0;i<10;i++)
  {
     (entries1[i].member)->next=&m4[i];
     (entries1[i].member)->next=NULL;
  }
  for(i=0;i<10;i++)
  {

    entries[i].state_id1=-10;

    entries[i].state_id2=-10;
  }
  
  count=pairingrelatedstates(M0,M1,entries,inputch,outputch);

  printf("\n count is %d\n",count);
 
  printf("\n ******** SIMULATION TABLE AFTER FIRST ITERATION ***********\n");
  printf("%s  %s",M0->states[entries[0].state_id1].state_id,M1->states[entries[0].state_id2].state_id);printf("\t");
  write_lists((entries[0].member)->term1);
  printf("\n");
  for(i=1;i<count;i++)
  {
   printf("%s  %s",M0->states[entries[i].state_id1].state_id,M1->states[entries[i].state_id2].state_id);printf("\t");
   write_lists((entries[i].member)->term1);
   printf(" = ");
   write_lists((entries[i].member)->term2);
   printf("\n");
  }
  
  for(i=0;i<count;i++)
  {
    entries1[i].state_id1=entries[i].state_id1;
    entries1[i].state_id2=entries[i].state_id2;
    (entries1[i].member)->term1=(entries[i].member)->term1;
    (entries1[i].member)->term2=(entries[i].member)->term2;
  }
  
  for(i=0;i<count;i++)
  {
    pair[i].ch=-99; 
    pair[i].y[1]=-99;//intialises the second target entry for every source as -99
  }
  
  findingfinalsrf(M0,M1,entries,entries1,pair,inputch,outputch,count,argv1);

  return 0;
	
}
 

  

