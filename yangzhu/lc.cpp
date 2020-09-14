#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;
struct pig{
	int pinzhong;
	double weight;
	int growday;
	int growmonth;
	int number;
	int isinfected;
	pig* next=NULL;
};
class pighouse{
	private:
		int count_number;
		pig* head;
		int isblackpighouse;
		int is_infected;
	public:
		pighouse();
		void add_pig(pig* p);
		double get_price();
		void weight_add(int ntime); 
		void distribute(int pz);
		void clearpighouse();
		int getpz(int i);
		int getblackpig_number();
		int getflowerpig_number();
		int getwhitepig_number();
		void sethead(pig* p){
			head=p;
		}
		void setcount_number(int m){
			count_number=m;
		}
		void setis_infected(int a){
			is_infected=a;
		} 
		int getis_infected(){
			return is_infected;
		}
		pig* gethead(){
			return head;
		}
		int getcount_number(){
			return count_number;
		}
		void setisblackpighouse(int i){
			isblackpighouse=i;
		}
		int getisblackpighouse(){
			return isblackpighouse;
		}
		int getpz1(){
	    	int count=0;
	    	for(int i=0;i<count_number;i++){
	    		if(getpz(i)==1)
	    		count++;
			}
			return count;
		}
		int getpz2(){
	    	int count=0;
	    	for(int i=0;i<count_number;i++){
	    		if (getpz(i)==2)
	    		count++;
			}
			return count;
		}
		int getpz3(){
	    	int count=0;
	    	for(int i=0;i<count_number;i++){
	    		if (getpz(i)==3)
	    		count++;
			}
			return count;
		}
};
int allpigs;
double money=0;
int month,day;
int sell_cnt=1;
int buy_cnt=1;
pighouse::pighouse(){
	count_number=0;
	head=NULL;
	isblackpighouse=0;
	is_infected=0;
}
void pighouse::clearpighouse(){
	if(head==NULL)
	return;
	else{
		pig* p=head;
		pig* p1=p;
		count_number=0;
		setisblackpighouse(0);
		head=NULL;
		head->next=NULL; 
		while(p){
			p1=p;
			p=p->next;
			delete p1;
		} 
		delete p;
  	}
}
int pighouse::getpz(int i){
	pig* p=head;
	for(int j=0;j<i&&p;j++){
		p=p->next;
	}
	return p->pinzhong;
}
void pighouse::add_pig(pig* p){
	count_number++;
	p->isinfected=0;
	p->next=NULL;
	if(head==NULL){
		head=p;
	}
	else{
		pig* p1=head;
		while(p1->next){
			p1=p1->next;
		}
		p1->next=p;
	}
}
double pighouse::get_price(){
	double sellprice=0;
	if(head==0)
		return 0;
	int months1,days1,flag=0;
	pig* p=head,*p1=p;
	while(p!=NULL){
		months1=p->growmonth;
		days1=p->growday;
		while(days1>=30){
			days1-=30;
			months1++;
		}
		if(months1>=12||p->weight>75){
			if(count_number==1){
				count_number--;
				setisblackpighouse(0);
				head=NULL;
				delete p;
				break;
			}
			if(p->pinzhong==1){
				sellprice+=30*p->weight; 
			}
			if(p->pinzhong=2){
				sellprice+=14*p->weight;
			}
			if(p->pinzhong=3)
				sellprice+=12*p->weight;
			p1->next=p->next;
			delete p;
			p=p1->next;
			count_number--;
			continue;
		}
		else if(flag==0){
			flag=1;
			head=p;
		}
		p1=p;
		p=p1->next;
	}
	return sellprice;
} 
void pighouse::weight_add(int ntime){
	srand((unsigned)time(NULL));
	pig* p=head;
	while(p){
		p->weight+=(double)(rand()%12)*ntime/10; 
		if(ntime==1)p->growday++;
		else p->growmonth++;
		p=p->next;
	}
}
int pighouse::getblackpig_number(){
	int num=0;
	if(head==NULL)
		return 0;
	else{
		for(pig *p=head;p!=NULL;p=p->next)
			if(p->pinzhong==1)
				num++;	
		return num;
	}
}
int pighouse::getflowerpig_number(){
	int num=0;
	if(head==NULL)
		return 0;
	else{
		for(pig *p=head;p!=NULL;p=p->next)
			if(p->pinzhong==2)
				num++;	
				return num;
	}
}
int pighouse::getwhitepig_number(){
	int num=0;
	if(head==NULL)
		return 0;
	else{
		for(pig *p=head;p!=NULL;p=p->next)
			if(p->pinzhong==3)
				num++;	
				return num;
	}
}
void pighouse::distribute(int pz){
	pig* p=new pig;
	srand((unsigned)time(NULL));
	p->pinzhong=pz;		
	p->weight=(rand()%(500-200+1)+200)/10.0;
	p->growmonth=0;	
	p->growday=0;
	if(head==NULL){
		p->number=0;
		p->next=NULL;
		head=p;
		count_number++;
		return;
	}
	if(head->number!=0){
		p->number=0;
		p->next=head;
		head=p;
		count_number++;
		return;
	}
	else {
	pig*p1=head,*p2=p1;
	int k=0;
	while(p1->number==k&&p1->next){
		k++;
		p2=p1;
		p1=p1->next;
	}
	if(p1->next==NULL){
		p->number=count_number;
		p->next=NULL;
		p1->next=p;
	}
	else{
		p->number=k;
		p2->next=p;
		p->next=p1;
	}
	count_number++;
	} 
}
int get_total_pig(pighouse *ph){
	int total_pig=0;
	for(int i=0;i<100;i++)
		 total_pig+=ph[i].getcount_number();
	return total_pig;
}
void print_pighouse(pighouse *ph,int bh){
	 cout<<"猪圈"<<bh<<":"<<endl;
	 if(ph[bh].getisblackpighouse()==1){
	 	cout<<"猪圈共有"<<ph[bh].getblackpig_number()<<"头黑猪"<<endl; 
	 }
	 else{
	 	if(ph[bh].getcount_number()==0)
	 		cout<<"猪圈共有"<<ph[bh].getcount_number()<<"头猪"<<endl;
	 	else{
	 		cout<<"猪圈共有"<<ph[bh].getcount_number()<<"头猪"<<endl;
	 		cout<<"其中小花猪"<<ph[bh].getflowerpig_number()<<"头,大花白猪"<<ph[bh].getwhitepig_number()<<"头"<<endl; 
		}
	}
	 if(ph[bh].getcount_number()!=0){
	 	pig* pp=ph[bh].gethead();
	 	while(pp){
	 		if(pp->pinzhong==1) 
				cout<<"种类 ：黑猪"<<endl;
			else if(pp->pinzhong==2)
				cout<<"种类 ：小花猪"<<endl;
			else cout<<"种类 ：大花白猪"<<endl;
			cout<<"重量 ："<<pp->weight<<"kg"<<endl;
			pp=pp->next;
		 }
	 		
	 }
}
void weight_distribution(pighouse ph[]){
	int b1=0,b2=0,b3=0,b4=0,f1=0,f2=0,f3=0,f4=0,w1=0,w2=0,w3=0,w4=0;
	for(int i=0;i<100;i++){
		pig *t=ph[i].gethead();
		while(t){
			if(t->pinzhong==1){
				if(t->weight<=50) b1++;
				else if(t->weight>50&&t->weight<=100) b2++;
				else if(t->weight>100&&t->weight<=150) b3++;
				else b4++;
			}
			else if(t->pinzhong==2){
				if(t->weight<=50) f1++;
				else if(t->weight>50&&t->weight<=100) f2++;
				else if(t->weight>100&&t->weight<=150) f3++;
				else f4++;
			}
			else {
				if(t->weight<=50) w1++;
				else if(t->weight>50&&t->weight<=100) w2++;
				else if(t->weight>100&&t->weight<=150) w3++;
				else w4++;
			}
			t=t->next;
		}
}
	cout<<"黑猪：\n";
	cout<<"体重在20~50kg的猪数量/头：   "<<b1<<endl;
	cout<<"体重在50~100kg的猪数量/头：  "<<b2<<endl;
	cout<<"体重在100~150kg的猪数量/头： "<<b3<<endl;
	cout<<"体重在150kg以上的猪数量/头： "<<b4<<endl; 
	cout<<"小花猪：\n";
	cout<<"体重在20~50kg的猪数量/头：   "<<f1<<endl;
	cout<<"体重在50~100kg的猪数量/头：  "<<f2<<endl;
	cout<<"体重在100~150kg的猪数量/头： "<<f3<<endl;
	cout<<"体重在150kg以上的猪数量/头： "<<f4<<endl; 
	cout<<"大花白猪：\n";
	cout<<"体重在20~50kg的猪数量/头：   "<<w1<<endl;
	cout<<"体重在50~100kg的猪数量/头：  "<<w2<<endl;
	cout<<"体重在100~150kg的猪数量/头： "<<w3<<endl;
	cout<<"体重在150kg以上的猪数量/头： "<<w4<<endl; 
	cout<<endl;
}
void raise_time_distribution(pighouse ph[]){
	int tb1=0,tb2=0,tb3=0,tb4=0,tb5=0,tf1=0,tf2=0,tf3=0,tf4=0,tf5=0,tw1=0,tw2=0,tw3=0,tw4=0,tw5=0;
	for(int i=0;i<100;i++){
		pig *rp=ph[i].gethead();
		while(rp){
			if(rp->pinzhong==1){
				if(rp->growmonth<3)
					tb1++;
				else if(rp->growmonth>=3&&rp->growmonth<6)
					tb2++;
				else if(rp->growmonth>=6&&rp->growmonth<9)
					tb3++;
				else if(rp->growmonth>9&&rp->growmonth<12)
					tb4++;
				else tb5++;
			}
			else if(rp->pinzhong==2){
				if(rp->growmonth<3)
					tf1++;
				else if(rp->growmonth>=3&&rp->growmonth<6)
					tf2++;
				else if(rp->growmonth>=6&&rp->growmonth<9)
					tf3++;
				else if(rp->growmonth>9&&rp->growmonth<12)
					tf4++;
				else tf5++;
			}
			else{
				if(rp->growmonth<3)
					tw1++;
				else if(rp->growmonth>=3&&rp->growmonth<6)
					tw2++;
				else if(rp->growmonth>=6&&rp->growmonth<9)
					tw3++;
				else if(rp->growmonth>9&&rp->growmonth<12)
					tw4++;
				else tw5++;
			}
			rp=rp->next;
		}
	}
	cout<<"黑猪：\n";
	cout<<"饲养时间在0~3个月的猪数量/头：   "<<tb1<<endl;
	cout<<"饲养时间在3~6个月的猪数量/头：   "<<tb2<<endl;
	cout<<"饲养时间在6~9个月的猪数量/头：   "<<tb3<<endl;
	cout<<"饲养时间在9~12个月的猪数量/头：  "<<tb4<<endl; 
	cout<<"饲养时间在12个月以上的猪数量/头："<<tb5<<endl;
	cout<<"小花猪：\n";
	cout<<"饲养时间在0~3个月的猪数量/头：   "<<tf1<<endl;
	cout<<"饲养时间在3~6个月的猪数量/头：   "<<tf2<<endl;
	cout<<"饲养时间在6~9个月的猪数量/头：   "<<tf3<<endl;
	cout<<"饲养时间在9~12个月的猪数量/头：  "<<tf4<<endl; 
	cout<<"饲养时间在12个月以上的猪数量/头："<<tf5<<endl;
	cout<<"大花白猪：\n";
	cout<<"饲养时间在0~3个月的猪数量/头：   "<<tw1<<endl;
	cout<<"饲养时间在3~6个月的猪数量/头：   "<<tw2<<endl;
	cout<<"饲养时间在6~9个月的猪数量/头：   "<<tw3<<endl;
	cout<<"饲养时间在9~12个月的猪数量/头：  "<<tw4<<endl; 
	cout<<"饲养时间在12个月以上的猪数量/头："<<tw5<<endl;
	cout<<endl;
} 
int get_number_of_blackpig(pighouse ph[]){
	int number=0;
	for(int i=0;i<100;i++)
		number+=ph[i].getblackpig_number();
	return number;
}
int get_number_of_flowerpig(pighouse ph[]){
	int number=0;
	for(int i=0;i<100;i++)
		number+=ph[i].getflowerpig_number();
	return number;
}
int get_number_of_whitepig(pighouse ph[]){
	int number=0;
	for(int i=0;i<100;i++)
		number+=ph[i].getwhitepig_number();
	return number;
}
void enter_new_pig(int blackpig,int flowerpig,int whitepig,pighouse ph[]){
	while(blackpig--){
		for(int i=0;i<100;i++){
			if(ph[i].getisblackpighouse()==1&&ph[i].getcount_number()<10){
				ph[i].distribute(1);
				break; 
			}
			if(ph[i].gethead()==NULL){
				ph[i].distribute(1);
				ph[i].setisblackpighouse(1);
				break;
			}
		}		
	}	
	int average=allpigs/100+1;
	while(1){
		for(int i=0;i<100;i++){
			if(ph[i].getisblackpighouse()==0){
				if(flowerpig>0&&ph[i].getcount_number()<=average){
					ph[i].distribute(2);
					flowerpig--;
				}
				if(whitepig>0&&ph[i].getcount_number()<=average){
					ph[i].distribute(3);
					whitepig--;
				}
			}
		}
		if(flowerpig==0&&whitepig==0)
			break;
	}
}
void save_5years(int price,int out_pig_number){
	ofstream outfive("近五年养猪场的销售购入情况.txt",ios::app);
	if(!outfive){
		cout<<"open file error!\n";
		exit(1);
	}
	outfive<<"第"<<sell_cnt<<"次出售猪数： "<<out_pig_number<<"头"<<endl;
	outfive<<"本次获利："<<price<<"元,累计收益为："<<money<<"元"<<endl;
	outfive.close();
}
void save_5years(int blackpig,int flowerpig,int whitepig){
	ofstream outfive("近五年养猪场的销售购入情况.txt",ios::app);
	if(!outfive){
		cout<<"open file error!\n";
		exit(1);
	}
	outfive<<"第"<<buy_cnt<<"次购猪："<<"黑猪: "<<blackpig<<"头 小花猪："<<flowerpig<<"头 大花白猪："<<whitepig<<"头"<<endl;
	outfive.close() ;
}
void save_data(pighouse *ph){
	ofstream data("data_save.txt");
	if(!data){
		cout<<"open file error!\n";
		exit(1); 
	}
	for(int i=0;i<100;i++){
		int g=ph[i].getcount_number();
		data<<g<<endl;
		if(g==0){
			continue;
		}
		else{
			pig* p=ph[i].gethead();
			while(g--){
				data<<p->pinzhong<<" "<<p->number<<" "<<p->weight<<" "<<p->growmonth<<" "<<p->growday<<endl;
				p=p->next;
			}
		}
	}
	data.close();
}
void save_global_variable(){
	ofstream outgv("global_variable_save.txt");
	if(!outgv){
		cout<<"open file error!\n";
		exit(1);
	}
	outgv<<allpigs<<" "<<buy_cnt<<" "<<sell_cnt<<" "<<month<<" "<<day<<" "<<money<<" "<<endl; 
}
void read_global_variable(){
	ifstream readgv("global_variable_save.txt");
	if(!readgv){
		cout<<"open file error!\n";
		exit(1);
	}
	else{
		readgv>>allpigs;
		readgv>>buy_cnt;
		readgv>>sell_cnt;
		readgv>>month;
		readgv>>day;
		readgv>>money;
		}
		cout<<allpigs<<" "<<buy_cnt<<" "<<sell_cnt<<" "<<month<<" "<<day<<" "<<money<<" "<<endl;
}
void read_data(pighouse *ph){
	ifstream fin("data_save.txt",ios::in);
	if(!fin){
		cout<<"open file error!\n";
		exit(1);
	}
	while(!fin.eof()){
		int cntnum;
		for(int j=0;j<100;j++){
		fin>>cntnum;
		ph[j].setcount_number(cntnum);
		int pz,gm,gd,n;
		double weigh;
		if(cntnum==0){
			continue;
		}
		else{	
			while(cntnum--){
				pig *p=new pig;
				fin>>pz>>n>>weigh>>gm>>gd;
				p->pinzhong=pz;
				if(p->pinzhong==1) ph[j].setisblackpighouse(1);
				p->number=n;
				p->weight=weigh;
				p->growmonth=gm; 
				p->growday=gd;
				ph[j].add_pig(p);
			}
		}
	}break;
	}
}

bool is_all_infected(pighouse *ph){
	for(int i=0;i<100;i++){
		if(ph[i].getcount_number()==0)
		continue;
		else{
			pig *p=ph[i].gethead();
			while(p!=NULL){
				if(p->isinfected!=1)
					return false;
				p=p->next;
			}
		}
	}
	return true;
}

int swine_fever(pighouse *ph){
	int deathdays=1;int j;
	srand((unsigned)time(NULL));
	int suijibianhao;
	while(1){
		suijibianhao=rand()%100+0;
		if(ph[suijibianhao].getcount_number()==0){
			suijibianhao=rand()%100+0;
			continue;
		}
		else{
			ph[suijibianhao].setis_infected(1);break;
		}
	}
	while(1){
		for(int i=0;i<100;i++){
			if(ph[i].getis_infected()==1){
					pig *ppp=ph[i].gethead();
					ppp->isinfected=1;ppp=ppp->next;
					while(ppp){
						int suijishu=rand()%2;
						if(suijishu==0){
							ppp=ppp->next;
						}
						else{
							ppp->isinfected=1;
							ppp=ppp->next;
						}
					}
			}
			j=i;
			
			if(ph[j].getis_infected()==1&&j>0&&j<99){
				int suijishu1=rand()%20+1;
				int suijishu2=rand()%20+1;
				if(suijishu1==1||suijishu1==2||suijishu1==3){
					if(ph[j-1].getis_infected()!=1) ph[j-1].setis_infected(1);
				}
				if(suijishu2==1||suijishu2==2||suijishu2==3){
					if(ph[j+1].getis_infected()!=1) ph[j+1].setis_infected(1);
				}
			}
		}
		deathdays++;
		if(is_all_infected(ph)) break;
	}
	return deathdays;
}

void gelicuoshi(pighouse ph[]){
	srand((unsigned)time(NULL));
	int suijishu1,dd;
	while(1){
		suijishu1=rand()%100+0;
		if(ph[suijishu1].getcount_number()==0){
			suijishu1=rand()%100+0;
			continue;
		}
		else break;
	}
		printf("现在已经发现发病猪在猪圈：%d\n",suijishu1); 
		if((suijishu1-2)>=0){
			int flag=ph[suijishu1-2].getisblackpighouse();
			int b=ph[suijishu1-2].getcount_number();
			int c;int j=0;
			dd=1; 
			if(flag==1){ 
				for(int i=0;i<100&&(i<suijishu1-2||i>suijishu1+2);i++){
					c=ph[i].getcount_number();
					if(ph[i].getisblackpighouse()==1&&c<10){
						cout<<"将猪圈 "<<suijishu1-2<<"的第"<<dd<<"头猪移到猪圈 "<<i<<"中\n"; 
						dd++;c++;
						b--;
					}
					if(b==0) break;
				}
			}
			else{
					for(int i=0;i<100&&(i<suijishu1-2||i>suijishu1+2);i++){
						c=ph[i].getcount_number();
					if(ph[i].getisblackpighouse()!=1&&c<10){
						cout<<"将猪圈 "<<suijishu1-2<<"的第"<<dd<<"头猪移到猪圈 "<<i<<"中\n"; 
						c++;j=i;
						dd++;b--;
					}if(b==0)
						break;					
					}
					
				}
		
		}
		if((suijishu1+2)<100){
			int flag=ph[suijishu1-2].getisblackpighouse();
			int a=ph[suijishu1+2].getcount_number();
			int d;dd=1;int j=0;		
				if(flag==1){
				for(int i=j;i<100&&(i<suijishu1-2||i>suijishu1+2);i++){
					d=ph[i].getcount_number();
					if(ph[i].getisblackpighouse()==1&&d<10){
						cout<<"将猪圈 "<<suijishu1+2<<"的第"<<dd<<"头猪移到猪圈 "<<i<<"中\n"; dd++;
							d++;j=i;a--;
					}
					if(a==0) break; 
				}
				}
				else{
					d=ph[suijishu1+2].getcount_number();
					for(int i=j;i<100&&(i<suijishu1-2||i>suijishu1+2);i++){
						if(ph[i].getisblackpighouse()!=1&&d<10){
						cout<<"将猪圈 "<<suijishu1+2<<"的第"<<dd<<"头猪移到猪圈 "<<i<<"中\n";
						dd++;d++;j=i;a--;
					}
					if(a==0) break;
				}
			}
		
	}
}

void menu(){
	cout<<"\n\n\n\n";
	cout<<"               欢迎来到养猪模拟游戏！\n\n";
	cout<<"您现在是养猪场的主人，养猪致富是您的目标！请合理的规划！\n";
	cout<<"          1:开始游戏\n";
	cout<<"          2:继续游戏\n";
	cout<<"          3:退出游戏\n"; 
	cout<<"\n\n\n"; 
} 
void menu_op(){
	cout<<"\n";
	cout<<"          1:初始化猪圈\n";
	cout<<"          2:查询\n";
	cout<<"          3:出售一批猪并新进一批猪\n";
	cout<<"          4:一天后\n";
	cout<<"          5:一个月后\n"; 
	cout<<"          6:重新游戏\n";
	cout<<"          7:保存游戏\n";
	cout<<"          8:猪瘟爆发\n";
	cout<<"          9:返回\n";
	cout<<"\n"; 
}

void zhuwen(){
	cout<<"\n";
	cout<<"          1:死亡模拟\n";
	cout<<"          2:控制措施\n";
	cout<<"          3:返回\n";
	cout<<"\n";
}

void chaxun(){
	cout<<"\n\n\n";
	cout<<"               查询          \n";
	cout<<"\n";
	cout<<"  1.查询当前某一猪圈的猪的数量和种类\n";
	cout<<"  2.查询当前某一猪圈某头猪的状态信息\n";
	cout<<"  3.统计当前猪场每个品种猪的数量和体重、饲养时间分布情况\n";
	cout<<"  4.查询近5年猪的销售记录和猪崽儿的购入记录（记录用文件形式存储)\n";
	cout<<"  5.返回\n";
	cout<<"\n";
}

void chaxun_3(){
	cout<<"\n";
	cout<<"  1.统计当前猪场每个品种猪的数量分布情况\n";
	cout<<"  2.统计当前猪场每个品种猪体重分布情况\n";
	cout<<"  3.统计当前猪场每个品种猪饲养时间分布情况\n";
	cout<<"  4.返回\n";
	cout<<"\n";
} 
int main(){
	pighouse ph[100];
	srand((unsigned)time(NULL));
	menu();	
	int o;
	do{
	cin>>o;
	while(1){
		if(o==1||o==2||o==3) break;
		else{
			cout<<"无效输入！请重新输入你要的操作：";
			cin>>o;
		}
	}
	if(o==2){
		read_global_variable();
		read_data(ph); 
		for(int i=0;i<100;i++){
			ph[i].setcount_number((ph[i].getcount_number())/2);
		}
		menu_op();
	int op;
	do{
		cout<<"请输入你要的操作："; 
		cin>>op;
		while(1){
			if(op==1||op==2||op==3||op==4||op==5||op==6||op==7||op==8||op==9) break;
			else {
				cout<<"无效输入！请重新输入你要的操作：";
				cin>>op; 
			}
		}
		if(op==6){
				for(int i=0;i<100;i++){
					ph[i].clearpighouse();
				}
				cout<<"游戏重新开始！\n";
				menu(); break;
			}
			if(op==9) {
				menu();
				break;
			}
		switch(op){
			case 1:{
				int bn,fn,wn;
				cout<<"请依次输入黑猪，小花猪，大花白猪的数量(三者数量之和不能超过1000)\n";
				cin>>bn>>fn>>wn;
				allpigs=bn+fn+wn;
				while(allpigs>1000){
					cout<<"错误！请重新输入\n"; 
					cin>>bn>>fn>>wn;
					allpigs=bn+fn+wn;
				} 
				enter_new_pig(bn,fn,wn,ph);
				save_5years(bn,fn,wn);
				buy_cnt++; 
				menu_op();
				break;
				}
			case 2:{
				do{
					chaxun();
					cout<<"请输入你要的操作："; 
					int opp;
					cin>>opp;
					if(opp==5) break;
					else switch(opp){
						case 1:{
							int bianhao;
							cout<<"请输入你想查询的猪圈编号：";
							cin>>bianhao;
							if(bianhao<0||bianhao>99){
							cout<<"当前编号的猪圈不存在！"<<endl;
							}	
							else{
								cout<<"猪圈"<<bianhao<<":"<<endl;
	 							if(ph[bianhao].getisblackpighouse()==1){
	 									cout<<"猪圈共有"<<ph[bianhao].getblackpig_number()<<"头黑猪"<<endl; 
	 							}
	 							else{
	 									if(ph[bianhao].getcount_number()==0)
	 									cout<<"猪圈共有"<<ph[bianhao].getcount_number()<<"头猪"<<endl;
	 									else{
	 											cout<<"猪圈共有"<<ph[bianhao].getcount_number()<<"头猪"<<endl;
	 											cout<<"其中小花猪"<<ph[bianhao].getflowerpig_number()<<"头,大花白猪"<<ph[bianhao].getwhitepig_number()<<"头"<<endl; 
											}
									}
									cout<<endl;
							}
					break;
				}
				        case 2:{
				        	int num1,num2;
							cout<<"请输入你想查询的猪圈编号\n";
							cin>>num1;
							while(1){
								if(num1<0||num1>99){
										cout<<"当前查询的猪圈不存在!"<<endl; 
										cout<<"请重新输入想查询的猪圈："<<endl;
										cin>>num1; 
								}
								else break;
								} 
								if(ph[num1].getcount_number()==0)
									cout<<"当前猪圈里面没有猪\n";
								else{
									cout<<"当前猪圈里有"<<ph[num1].getcount_number()<<"头猪\n";
									cout<<"你想查询第几头猪？请输入序号：";
								cin>>num2;
								while(1){
									if(num2<1||num2>ph[num1].getcount_number()){
									cout<<"输入数字无效！\n";
									cout<<"请重新输入：";
									cin>>num2; 
									}
									else break;
								}
								pig *cp=ph[num1].gethead();
								for(int i=2;i<=num2;i++)
									cp=cp->next;
								if(cp->pinzhong==1) 
									cout<<"种类 ：黑猪"<<endl;
								else if(cp->pinzhong==2)
									cout<<"种类 ：小花猪"<<endl;
								else 
								cout<<"种类    ：大花白猪"<<endl;
								cout<<"体重    ："<<cp->weight<<"kg"<<endl;
								cout<<"饲养时间："<<cp->growmonth<<"个月"<<cp->growday<<"天"<<endl;
								cout<<endl; 
							} 
							break;
						}
				        case 3:{
				        	int opr;
				        	do{
								chaxun_3();
				        		cout<<"请输入你想要的操作： ";
								cin>>opr; 
				        		while(1){
				        			if(opr==1||opr==2||opr==3||opr==4){
				        				break;
									}else{
										cout<<"无效输入！请重新输入你想要的操作： ";
										cin>>opr; 
									}
								}
								if(opr==4)break;	
								else{
									switch(opr){
									case 1:{
										cout<<"当前猪场每一品种猪的数量分布：\n";
										cout<<"黑猪共有"<<get_number_of_blackpig(ph)<<"头"<<endl;
										cout<<"小花猪共有"<<get_number_of_flowerpig(ph)<<"头"<<endl;
										cout<<"大花白猪共有"<<get_number_of_whitepig(ph)<<"头"<<endl;
										cout<<endl;
										break;
									}
									case 2:{
										weight_distribution(ph);
										break;
									}
									case 3:{
										raise_time_distribution(ph);
										break;
									}
									default:break;
								}
								}
							}while(1);
					break;
				}
				        case 4:{
					cout<<"    已保存！\n"; 
					break;
				}
				        case 5:{
					break;
				}
				default: break;
				}
			}while(1);
					menu_op();
					break;
			}
			case 3:{
				if(month+day/30<3){
					cout<<"距离上次出圈时间不足3个月，请再饲养一段时间！"<<endl;
					break;
				}
				double price=0;
				for(int i=0;i<100;i++){
						price+=ph[i].get_price();
				}
				int temp=get_total_pig(ph);
				int out_pig_number=allpigs-temp;
				allpigs=temp;
				money+=price;
				cout<<"此次圈出猪"<<out_pig_number<<"头，总体售价为:"<<(int)price<<"元,累计收益为："<<(int)money<<"元"<<endl;
				
				int blackpig=0,kongpighouse=0,count=0;
				for(int i=0;i<100;i++){
					if(ph[i].getcount_number()==0){
						kongpighouse++;
						continue;
					}
					if(ph[i].getpz1())
						blackpig+=10-ph[i].getpz1();
					else count+=10-ph[i].getcount_number();
						}
					int bpig,fpig,wpig;
					cout<<"本农场剩余猪位："<<1000-allpigs<<endl; 
					cout<<"请依次输入本次购入的黑猪，小花猪，大花白猪数：\n";
					cin>>bpig>>fpig>>wpig;
					while(1){
							if(bpig>blackpig+kongpighouse*10||fpig>kongpighouse*10+count||wpig>kongpighouse*10+count||fpig+wpig>kongpighouse*10+count)
								cout<<"超过猪场最大容纳量,请重新输入\n";
							else if(((kongpighouse-(bpig-blackpig)/10)*10<=fpig+wpig)&&bpig>blackpig)
								cout<<"错误！黑猪与其他猪不能混养！请重新输入：\n";
							else break; 
							cin>>bpig>>fpig>>wpig;
						}
					allpigs+=bpig+fpig+wpig;
					enter_new_pig(bpig,fpig,wpig,ph);
					save_5years(price,out_pig_number);
					save_5years(bpig,fpig,wpig);
					buy_cnt++;
					sell_cnt++;
					while(day>=30){
							day-=30;
							month++;
						}
					month-=3;
				menu_op();
				break;
			}
			case 4:{
				for(int i=0;i<100;i++){
					ph[i].weight_add(1);
				}
				day++;
				menu_op();
				break;
			}
			case 5:{
				for(int i=0;i<100;i++){
					ph[i].weight_add(30);
				}
				month++;
				menu_op();
				break;
			}
			case 7:{
				save_data(ph);
				cout<<"   已保存！   \n"; 
				break;
			}
			case 8:{
				zhuwen();
				int zhuwen_op;
				cin>>zhuwen_op;
				while(1){
					if(zhuwen_op==1||zhuwen_op==2||zhuwen_op==3) break;
					else cin>>zhuwen_op;
				}
				do{
					switch(zhuwen_op){
						case 1:{
							cout<<swine_fever(ph)<<endl;
							break;
						}
						case 2:{
							gelicuoshi(ph);
							break;
						}
						default:break;
					}
					menu_op();
					break;
				}while(1);
				break;
			}
			default:{
				break;
			}
			}
	}while(1);
	}
	else if(o==1){
		menu_op();
	int op;
	do{
		cout<<"请输入你要的操作："; 
		cin>>op;
		while(1){
			if(op==1||op==2||op==3||op==4||op==5||op==6||op==7||op==8||op==9) break;
			else {
				cout<<"无效输入！请重新输入你要的操作：";
				cin>>op; 
			}
		}
		if(op==6){
				for(int i=0;i<100;i++){
					ph[i].clearpighouse();
				}
				cout<<"游戏重新开始！\n";
				menu(); break;
			}
			if(op==9) {
				menu();
				break;
			}
		switch(op){
			case 1:{
				int bn,fn,wn;
				cout<<"请依次输入黑猪，小花猪，大花白猪的数量(三者数量之和不能超过1000)\n";
				cin>>bn>>fn>>wn;
				allpigs=bn+fn+wn;
				while(allpigs>1000){
					cout<<"错误！请重新输入\n"; 
					cin>>bn>>fn>>wn;
					allpigs=bn+fn+wn;
				} 
				enter_new_pig(bn,fn,wn,ph);
				save_5years(bn,fn,wn);
				buy_cnt++; 
				menu_op();
				break;
				}
			case 2:{
				do{
					chaxun();
					cout<<"请输入你要的操作："; 
					int opp;
					cin>>opp;
					if(opp==5) break;
					else switch(opp){
						case 1:{
							int bianhao;
							cout<<"请输入你想查询的猪圈编号：";
							cin>>bianhao;
							if(bianhao<0||bianhao>99){
							cout<<"当前编号的猪圈不存在！"<<endl;
							}	
							else{
								cout<<"猪圈"<<bianhao<<":"<<endl;
	 							if(ph[bianhao].getisblackpighouse()==1){
	 									cout<<"猪圈共有"<<ph[bianhao].getblackpig_number()<<"头黑猪"<<endl; 
	 							}
	 							else{
	 									if(ph[bianhao].getcount_number()==2)
	 									cout<<"猪圈共有"<<ph[bianhao].getcount_number()<<"头猪"<<endl;
	 									else{
	 											cout<<"猪圈共有"<<ph[bianhao].getcount_number()<<"头猪"<<endl;
	 											cout<<"其中小花猪"<<ph[bianhao].getflowerpig_number()<<"头,大花白猪"<<ph[bianhao].getwhitepig_number()<<"头"<<endl; 
											}
									}
									cout<<endl;
							}
					break;
				}
				        case 2:{
				        	int num1,num2;
							cout<<"请输入你想查询的猪圈编号\n";
							cin>>num1;
							while(1){
								if(num1<0||num1>99){
										cout<<"当前查询的猪圈不存在!"<<endl; 
										cout<<"请重新输入想查询的猪圈："<<endl;
										cin>>num1; 
								}
								else break;
								} 
								if(ph[num1].getcount_number()==0)
									cout<<"当前猪圈里面没有猪\n";
								else{
									cout<<"当前猪圈里有"<<ph[num1].getcount_number()<<"头猪\n";
									cout<<"你想查询第几头猪？请输入序号：";
								cin>>num2;
								while(1){
									if(num2<1||num2>ph[num1].getcount_number()){
									cout<<"输入数字无效！\n";
									cout<<"请重新输入：";
									cin>>num2; 
									}
									else break;
								}
								pig *cp=ph[num1].gethead();
								for(int i=2;i<=num2;i++)
									cp=cp->next;
								if(cp->pinzhong==1) 
									cout<<"种类 ：黑猪"<<endl;
								else if(cp->pinzhong==2)
									cout<<"种类 ：小花猪"<<endl;
								else 
								cout<<"种类    ：大花白猪"<<endl;
								cout<<"体重    ："<<cp->weight<<"kg"<<endl;
								cout<<"饲养时间："<<cp->growmonth<<"个月"<<cp->growday<<"天"<<endl;
								cout<<endl; 
							} 
							break;
						}
				        case 3:{
				        	int opr;
				        	do{
								chaxun_3();
				        		cout<<"请输入你想要的操作： ";
								cin>>opr; 
				        		while(1){
				        			if(opr==1||opr==2||opr==3||opr==4){
				        				break;
									}else{
										cout<<"无效输入！请重新输入你想要的操作： ";
										cin>>opr; 
									}
								}
								if(opr==4)break;	
								else{
									switch(opr){
									case 1:{
										cout<<"当前猪场每一品种猪的数量分布：\n";
										cout<<"黑猪共有"<<get_number_of_blackpig(ph)<<"头"<<endl;
										cout<<"小花猪共有"<<get_number_of_flowerpig(ph)<<"头"<<endl;
										cout<<"大花白猪共有"<<get_number_of_whitepig(ph)<<"头"<<endl;
										cout<<endl;
										break;
									}
									case 2:{
										weight_distribution(ph);
										break;
									}
									case 3:{
										raise_time_distribution(ph);
										break;
									}
									default:break;
								}
								}
							}while(1);
					break;
				}
				        case 4:{
					cout<<"    已保存！\n"; 
					break;
				}
				        case 5:{
					break;
				}
				default: break;
				}
			}while(1);
					menu_op();
					break;
			}
			case 3:{
				if(month+day/30<3){
					cout<<"距离上次出圈时间不足3个月，请再饲养一段时间！"<<endl;
					break;
				}
				double price=0;
				for(int i=0;i<100;i++){
						price+=ph[i].get_price();
				}
				int temp=get_total_pig(ph);
				int out_pig_number=allpigs-temp;
				allpigs=temp;
				money+=price;
				cout<<"此次圈出猪"<<out_pig_number<<"头，总体售价为:"<<(int)price<<"元,累计收益为："<<(int)money<<"元"<<endl;
				
				int blackpig=0,kongpighouse=0,count=0;
				for(int i=0;i<100;i++){
					if(ph[i].getcount_number()==0){
						kongpighouse++;
						continue;
					}
					if(ph[i].getpz1())
						blackpig+=10-ph[i].getpz1();
					else count+=10-ph[i].getcount_number();
						}
					int bpig,fpig,wpig;
					cout<<"本农场剩余猪位："<<1000-allpigs<<endl; 
					cout<<"请依次输入本次购入的黑猪，小花猪，大花白猪数：\n";
					cin>>bpig>>fpig>>wpig;
					while(1){
							if(bpig>blackpig+kongpighouse*10||fpig>kongpighouse*10+count||wpig>kongpighouse*10+count||fpig+wpig>kongpighouse*10+count)
								cout<<"超过猪场最大容纳量,请重新输入\n";
							else if(((kongpighouse-(bpig-blackpig)/10)*10<=fpig+wpig)&&bpig>blackpig)
								cout<<"错误！黑猪与其他猪不能混养！请重新输入：\n";
							else break; 
							cin>>bpig>>fpig>>wpig;
						}
					allpigs+=bpig+fpig+wpig;
					enter_new_pig(bpig,fpig,wpig,ph);
					save_5years(price,out_pig_number);
					save_5years(bpig,fpig,wpig);
					buy_cnt++;
					sell_cnt++;
					while(day>=30){
							day-=30;
							month++;
						}
					month-=3;
				menu_op();
				break;
			}
			case 4:{
				for(int i=0;i<100;i++){
					ph[i].weight_add(1);
				}
				day++;
				menu_op();
				break;
			}
			case 5:{
				for(int i=0;i<100;i++){
					ph[i].weight_add(30);
				}
				month++;
				menu_op;
				break;
			}
			case 7:{
				save_data(ph);
				save_global_variable();
				for(int i=0;i<100;i++){
					ph[i].clearpighouse();
				}
				cout<<"   已保存！   \n"; 
				break;
			}
			case 8:{
				zhuwen();
				int zhuwen_op;
				cin>>zhuwen_op;
				while(1){
					if(zhuwen_op==1||zhuwen_op==2||zhuwen_op==3) break;
					else cin>>zhuwen_op;
				}
				do{
					switch(zhuwen_op){
						case 1:{
							cout<<swine_fever(ph)<<endl;
							break;
						}
						case 2:{
							gelicuoshi(ph);
							break;
						}
						default:break;
					}
					menu_op();
					break;
				}while(1);
				break;
			}
			default:{
				break;
			}
			}
	}while(1);
	}
	else{
			cout<<"        游戏结束\n";
			break;
		}
		}while(1);
	return 0;
}
