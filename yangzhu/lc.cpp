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
	 cout<<"��Ȧ"<<bh<<":"<<endl;
	 if(ph[bh].getisblackpighouse()==1){
	 	cout<<"��Ȧ����"<<ph[bh].getblackpig_number()<<"ͷ����"<<endl; 
	 }
	 else{
	 	if(ph[bh].getcount_number()==0)
	 		cout<<"��Ȧ����"<<ph[bh].getcount_number()<<"ͷ��"<<endl;
	 	else{
	 		cout<<"��Ȧ����"<<ph[bh].getcount_number()<<"ͷ��"<<endl;
	 		cout<<"����С����"<<ph[bh].getflowerpig_number()<<"ͷ,�󻨰���"<<ph[bh].getwhitepig_number()<<"ͷ"<<endl; 
		}
	}
	 if(ph[bh].getcount_number()!=0){
	 	pig* pp=ph[bh].gethead();
	 	while(pp){
	 		if(pp->pinzhong==1) 
				cout<<"���� ������"<<endl;
			else if(pp->pinzhong==2)
				cout<<"���� ��С����"<<endl;
			else cout<<"���� ���󻨰���"<<endl;
			cout<<"���� ��"<<pp->weight<<"kg"<<endl;
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
	cout<<"����\n";
	cout<<"������20~50kg��������/ͷ��   "<<b1<<endl;
	cout<<"������50~100kg��������/ͷ��  "<<b2<<endl;
	cout<<"������100~150kg��������/ͷ�� "<<b3<<endl;
	cout<<"������150kg���ϵ�������/ͷ�� "<<b4<<endl; 
	cout<<"С����\n";
	cout<<"������20~50kg��������/ͷ��   "<<f1<<endl;
	cout<<"������50~100kg��������/ͷ��  "<<f2<<endl;
	cout<<"������100~150kg��������/ͷ�� "<<f3<<endl;
	cout<<"������150kg���ϵ�������/ͷ�� "<<f4<<endl; 
	cout<<"�󻨰���\n";
	cout<<"������20~50kg��������/ͷ��   "<<w1<<endl;
	cout<<"������50~100kg��������/ͷ��  "<<w2<<endl;
	cout<<"������100~150kg��������/ͷ�� "<<w3<<endl;
	cout<<"������150kg���ϵ�������/ͷ�� "<<w4<<endl; 
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
	cout<<"����\n";
	cout<<"����ʱ����0~3���µ�������/ͷ��   "<<tb1<<endl;
	cout<<"����ʱ����3~6���µ�������/ͷ��   "<<tb2<<endl;
	cout<<"����ʱ����6~9���µ�������/ͷ��   "<<tb3<<endl;
	cout<<"����ʱ����9~12���µ�������/ͷ��  "<<tb4<<endl; 
	cout<<"����ʱ����12�������ϵ�������/ͷ��"<<tb5<<endl;
	cout<<"С����\n";
	cout<<"����ʱ����0~3���µ�������/ͷ��   "<<tf1<<endl;
	cout<<"����ʱ����3~6���µ�������/ͷ��   "<<tf2<<endl;
	cout<<"����ʱ����6~9���µ�������/ͷ��   "<<tf3<<endl;
	cout<<"����ʱ����9~12���µ�������/ͷ��  "<<tf4<<endl; 
	cout<<"����ʱ����12�������ϵ�������/ͷ��"<<tf5<<endl;
	cout<<"�󻨰���\n";
	cout<<"����ʱ����0~3���µ�������/ͷ��   "<<tw1<<endl;
	cout<<"����ʱ����3~6���µ�������/ͷ��   "<<tw2<<endl;
	cout<<"����ʱ����6~9���µ�������/ͷ��   "<<tw3<<endl;
	cout<<"����ʱ����9~12���µ�������/ͷ��  "<<tw4<<endl; 
	cout<<"����ʱ����12�������ϵ�������/ͷ��"<<tw5<<endl;
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
	ofstream outfive("���������������۹������.txt",ios::app);
	if(!outfive){
		cout<<"open file error!\n";
		exit(1);
	}
	outfive<<"��"<<sell_cnt<<"�γ��������� "<<out_pig_number<<"ͷ"<<endl;
	outfive<<"���λ�����"<<price<<"Ԫ,�ۼ�����Ϊ��"<<money<<"Ԫ"<<endl;
	outfive.close();
}
void save_5years(int blackpig,int flowerpig,int whitepig){
	ofstream outfive("���������������۹������.txt",ios::app);
	if(!outfive){
		cout<<"open file error!\n";
		exit(1);
	}
	outfive<<"��"<<buy_cnt<<"�ι���"<<"����: "<<blackpig<<"ͷ С����"<<flowerpig<<"ͷ �󻨰���"<<whitepig<<"ͷ"<<endl;
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
		printf("�����Ѿ����ַ���������Ȧ��%d\n",suijishu1); 
		if((suijishu1-2)>=0){
			int flag=ph[suijishu1-2].getisblackpighouse();
			int b=ph[suijishu1-2].getcount_number();
			int c;int j=0;
			dd=1; 
			if(flag==1){ 
				for(int i=0;i<100&&(i<suijishu1-2||i>suijishu1+2);i++){
					c=ph[i].getcount_number();
					if(ph[i].getisblackpighouse()==1&&c<10){
						cout<<"����Ȧ "<<suijishu1-2<<"�ĵ�"<<dd<<"ͷ���Ƶ���Ȧ "<<i<<"��\n"; 
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
						cout<<"����Ȧ "<<suijishu1-2<<"�ĵ�"<<dd<<"ͷ���Ƶ���Ȧ "<<i<<"��\n"; 
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
						cout<<"����Ȧ "<<suijishu1+2<<"�ĵ�"<<dd<<"ͷ���Ƶ���Ȧ "<<i<<"��\n"; dd++;
							d++;j=i;a--;
					}
					if(a==0) break; 
				}
				}
				else{
					d=ph[suijishu1+2].getcount_number();
					for(int i=j;i<100&&(i<suijishu1-2||i>suijishu1+2);i++){
						if(ph[i].getisblackpighouse()!=1&&d<10){
						cout<<"����Ȧ "<<suijishu1+2<<"�ĵ�"<<dd<<"ͷ���Ƶ���Ȧ "<<i<<"��\n";
						dd++;d++;j=i;a--;
					}
					if(a==0) break;
				}
			}
		
	}
}

void menu(){
	cout<<"\n\n\n\n";
	cout<<"               ��ӭ��������ģ����Ϸ��\n\n";
	cout<<"�����������������ˣ������¸�������Ŀ�꣡�����Ĺ滮��\n";
	cout<<"          1:��ʼ��Ϸ\n";
	cout<<"          2:������Ϸ\n";
	cout<<"          3:�˳���Ϸ\n"; 
	cout<<"\n\n\n"; 
} 
void menu_op(){
	cout<<"\n";
	cout<<"          1:��ʼ����Ȧ\n";
	cout<<"          2:��ѯ\n";
	cout<<"          3:����һ�����½�һ����\n";
	cout<<"          4:һ���\n";
	cout<<"          5:һ���º�\n"; 
	cout<<"          6:������Ϸ\n";
	cout<<"          7:������Ϸ\n";
	cout<<"          8:��������\n";
	cout<<"          9:����\n";
	cout<<"\n"; 
}

void zhuwen(){
	cout<<"\n";
	cout<<"          1:����ģ��\n";
	cout<<"          2:���ƴ�ʩ\n";
	cout<<"          3:����\n";
	cout<<"\n";
}

void chaxun(){
	cout<<"\n\n\n";
	cout<<"               ��ѯ          \n";
	cout<<"\n";
	cout<<"  1.��ѯ��ǰĳһ��Ȧ���������������\n";
	cout<<"  2.��ѯ��ǰĳһ��Ȧĳͷ���״̬��Ϣ\n";
	cout<<"  3.ͳ�Ƶ�ǰ��ÿ��Ʒ��������������ء�����ʱ��ֲ����\n";
	cout<<"  4.��ѯ��5��������ۼ�¼�����̶��Ĺ����¼����¼���ļ���ʽ�洢)\n";
	cout<<"  5.����\n";
	cout<<"\n";
}

void chaxun_3(){
	cout<<"\n";
	cout<<"  1.ͳ�Ƶ�ǰ��ÿ��Ʒ����������ֲ����\n";
	cout<<"  2.ͳ�Ƶ�ǰ��ÿ��Ʒ�������طֲ����\n";
	cout<<"  3.ͳ�Ƶ�ǰ��ÿ��Ʒ��������ʱ��ֲ����\n";
	cout<<"  4.����\n";
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
			cout<<"��Ч���룡������������Ҫ�Ĳ�����";
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
		cout<<"��������Ҫ�Ĳ�����"; 
		cin>>op;
		while(1){
			if(op==1||op==2||op==3||op==4||op==5||op==6||op==7||op==8||op==9) break;
			else {
				cout<<"��Ч���룡������������Ҫ�Ĳ�����";
				cin>>op; 
			}
		}
		if(op==6){
				for(int i=0;i<100;i++){
					ph[i].clearpighouse();
				}
				cout<<"��Ϸ���¿�ʼ��\n";
				menu(); break;
			}
			if(op==9) {
				menu();
				break;
			}
		switch(op){
			case 1:{
				int bn,fn,wn;
				cout<<"�������������С�����󻨰��������(��������֮�Ͳ��ܳ���1000)\n";
				cin>>bn>>fn>>wn;
				allpigs=bn+fn+wn;
				while(allpigs>1000){
					cout<<"��������������\n"; 
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
					cout<<"��������Ҫ�Ĳ�����"; 
					int opp;
					cin>>opp;
					if(opp==5) break;
					else switch(opp){
						case 1:{
							int bianhao;
							cout<<"�����������ѯ����Ȧ��ţ�";
							cin>>bianhao;
							if(bianhao<0||bianhao>99){
							cout<<"��ǰ��ŵ���Ȧ�����ڣ�"<<endl;
							}	
							else{
								cout<<"��Ȧ"<<bianhao<<":"<<endl;
	 							if(ph[bianhao].getisblackpighouse()==1){
	 									cout<<"��Ȧ����"<<ph[bianhao].getblackpig_number()<<"ͷ����"<<endl; 
	 							}
	 							else{
	 									if(ph[bianhao].getcount_number()==0)
	 									cout<<"��Ȧ����"<<ph[bianhao].getcount_number()<<"ͷ��"<<endl;
	 									else{
	 											cout<<"��Ȧ����"<<ph[bianhao].getcount_number()<<"ͷ��"<<endl;
	 											cout<<"����С����"<<ph[bianhao].getflowerpig_number()<<"ͷ,�󻨰���"<<ph[bianhao].getwhitepig_number()<<"ͷ"<<endl; 
											}
									}
									cout<<endl;
							}
					break;
				}
				        case 2:{
				        	int num1,num2;
							cout<<"�����������ѯ����Ȧ���\n";
							cin>>num1;
							while(1){
								if(num1<0||num1>99){
										cout<<"��ǰ��ѯ����Ȧ������!"<<endl; 
										cout<<"�������������ѯ����Ȧ��"<<endl;
										cin>>num1; 
								}
								else break;
								} 
								if(ph[num1].getcount_number()==0)
									cout<<"��ǰ��Ȧ����û����\n";
								else{
									cout<<"��ǰ��Ȧ����"<<ph[num1].getcount_number()<<"ͷ��\n";
									cout<<"�����ѯ�ڼ�ͷ����������ţ�";
								cin>>num2;
								while(1){
									if(num2<1||num2>ph[num1].getcount_number()){
									cout<<"����������Ч��\n";
									cout<<"���������룺";
									cin>>num2; 
									}
									else break;
								}
								pig *cp=ph[num1].gethead();
								for(int i=2;i<=num2;i++)
									cp=cp->next;
								if(cp->pinzhong==1) 
									cout<<"���� ������"<<endl;
								else if(cp->pinzhong==2)
									cout<<"���� ��С����"<<endl;
								else 
								cout<<"����    ���󻨰���"<<endl;
								cout<<"����    ��"<<cp->weight<<"kg"<<endl;
								cout<<"����ʱ�䣺"<<cp->growmonth<<"����"<<cp->growday<<"��"<<endl;
								cout<<endl; 
							} 
							break;
						}
				        case 3:{
				        	int opr;
				        	do{
								chaxun_3();
				        		cout<<"����������Ҫ�Ĳ����� ";
								cin>>opr; 
				        		while(1){
				        			if(opr==1||opr==2||opr==3||opr==4){
				        				break;
									}else{
										cout<<"��Ч���룡��������������Ҫ�Ĳ����� ";
										cin>>opr; 
									}
								}
								if(opr==4)break;	
								else{
									switch(opr){
									case 1:{
										cout<<"��ǰ��ÿһƷ����������ֲ���\n";
										cout<<"������"<<get_number_of_blackpig(ph)<<"ͷ"<<endl;
										cout<<"С������"<<get_number_of_flowerpig(ph)<<"ͷ"<<endl;
										cout<<"�󻨰�����"<<get_number_of_whitepig(ph)<<"ͷ"<<endl;
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
					cout<<"    �ѱ��棡\n"; 
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
					cout<<"�����ϴγ�Ȧʱ�䲻��3���£���������һ��ʱ�䣡"<<endl;
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
				cout<<"�˴�Ȧ����"<<out_pig_number<<"ͷ�������ۼ�Ϊ:"<<(int)price<<"Ԫ,�ۼ�����Ϊ��"<<(int)money<<"Ԫ"<<endl;
				
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
					cout<<"��ũ��ʣ����λ��"<<1000-allpigs<<endl; 
					cout<<"���������뱾�ι���ĺ���С�����󻨰�������\n";
					cin>>bpig>>fpig>>wpig;
					while(1){
							if(bpig>blackpig+kongpighouse*10||fpig>kongpighouse*10+count||wpig>kongpighouse*10+count||fpig+wpig>kongpighouse*10+count)
								cout<<"���������������,����������\n";
							else if(((kongpighouse-(bpig-blackpig)/10)*10<=fpig+wpig)&&bpig>blackpig)
								cout<<"���󣡺������������ܻ��������������룺\n";
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
				cout<<"   �ѱ��棡   \n"; 
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
		cout<<"��������Ҫ�Ĳ�����"; 
		cin>>op;
		while(1){
			if(op==1||op==2||op==3||op==4||op==5||op==6||op==7||op==8||op==9) break;
			else {
				cout<<"��Ч���룡������������Ҫ�Ĳ�����";
				cin>>op; 
			}
		}
		if(op==6){
				for(int i=0;i<100;i++){
					ph[i].clearpighouse();
				}
				cout<<"��Ϸ���¿�ʼ��\n";
				menu(); break;
			}
			if(op==9) {
				menu();
				break;
			}
		switch(op){
			case 1:{
				int bn,fn,wn;
				cout<<"�������������С�����󻨰��������(��������֮�Ͳ��ܳ���1000)\n";
				cin>>bn>>fn>>wn;
				allpigs=bn+fn+wn;
				while(allpigs>1000){
					cout<<"��������������\n"; 
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
					cout<<"��������Ҫ�Ĳ�����"; 
					int opp;
					cin>>opp;
					if(opp==5) break;
					else switch(opp){
						case 1:{
							int bianhao;
							cout<<"�����������ѯ����Ȧ��ţ�";
							cin>>bianhao;
							if(bianhao<0||bianhao>99){
							cout<<"��ǰ��ŵ���Ȧ�����ڣ�"<<endl;
							}	
							else{
								cout<<"��Ȧ"<<bianhao<<":"<<endl;
	 							if(ph[bianhao].getisblackpighouse()==1){
	 									cout<<"��Ȧ����"<<ph[bianhao].getblackpig_number()<<"ͷ����"<<endl; 
	 							}
	 							else{
	 									if(ph[bianhao].getcount_number()==2)
	 									cout<<"��Ȧ����"<<ph[bianhao].getcount_number()<<"ͷ��"<<endl;
	 									else{
	 											cout<<"��Ȧ����"<<ph[bianhao].getcount_number()<<"ͷ��"<<endl;
	 											cout<<"����С����"<<ph[bianhao].getflowerpig_number()<<"ͷ,�󻨰���"<<ph[bianhao].getwhitepig_number()<<"ͷ"<<endl; 
											}
									}
									cout<<endl;
							}
					break;
				}
				        case 2:{
				        	int num1,num2;
							cout<<"�����������ѯ����Ȧ���\n";
							cin>>num1;
							while(1){
								if(num1<0||num1>99){
										cout<<"��ǰ��ѯ����Ȧ������!"<<endl; 
										cout<<"�������������ѯ����Ȧ��"<<endl;
										cin>>num1; 
								}
								else break;
								} 
								if(ph[num1].getcount_number()==0)
									cout<<"��ǰ��Ȧ����û����\n";
								else{
									cout<<"��ǰ��Ȧ����"<<ph[num1].getcount_number()<<"ͷ��\n";
									cout<<"�����ѯ�ڼ�ͷ����������ţ�";
								cin>>num2;
								while(1){
									if(num2<1||num2>ph[num1].getcount_number()){
									cout<<"����������Ч��\n";
									cout<<"���������룺";
									cin>>num2; 
									}
									else break;
								}
								pig *cp=ph[num1].gethead();
								for(int i=2;i<=num2;i++)
									cp=cp->next;
								if(cp->pinzhong==1) 
									cout<<"���� ������"<<endl;
								else if(cp->pinzhong==2)
									cout<<"���� ��С����"<<endl;
								else 
								cout<<"����    ���󻨰���"<<endl;
								cout<<"����    ��"<<cp->weight<<"kg"<<endl;
								cout<<"����ʱ�䣺"<<cp->growmonth<<"����"<<cp->growday<<"��"<<endl;
								cout<<endl; 
							} 
							break;
						}
				        case 3:{
				        	int opr;
				        	do{
								chaxun_3();
				        		cout<<"����������Ҫ�Ĳ����� ";
								cin>>opr; 
				        		while(1){
				        			if(opr==1||opr==2||opr==3||opr==4){
				        				break;
									}else{
										cout<<"��Ч���룡��������������Ҫ�Ĳ����� ";
										cin>>opr; 
									}
								}
								if(opr==4)break;	
								else{
									switch(opr){
									case 1:{
										cout<<"��ǰ��ÿһƷ����������ֲ���\n";
										cout<<"������"<<get_number_of_blackpig(ph)<<"ͷ"<<endl;
										cout<<"С������"<<get_number_of_flowerpig(ph)<<"ͷ"<<endl;
										cout<<"�󻨰�����"<<get_number_of_whitepig(ph)<<"ͷ"<<endl;
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
					cout<<"    �ѱ��棡\n"; 
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
					cout<<"�����ϴγ�Ȧʱ�䲻��3���£���������һ��ʱ�䣡"<<endl;
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
				cout<<"�˴�Ȧ����"<<out_pig_number<<"ͷ�������ۼ�Ϊ:"<<(int)price<<"Ԫ,�ۼ�����Ϊ��"<<(int)money<<"Ԫ"<<endl;
				
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
					cout<<"��ũ��ʣ����λ��"<<1000-allpigs<<endl; 
					cout<<"���������뱾�ι���ĺ���С�����󻨰�������\n";
					cin>>bpig>>fpig>>wpig;
					while(1){
							if(bpig>blackpig+kongpighouse*10||fpig>kongpighouse*10+count||wpig>kongpighouse*10+count||fpig+wpig>kongpighouse*10+count)
								cout<<"���������������,����������\n";
							else if(((kongpighouse-(bpig-blackpig)/10)*10<=fpig+wpig)&&bpig>blackpig)
								cout<<"���󣡺������������ܻ��������������룺\n";
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
				cout<<"   �ѱ��棡   \n"; 
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
			cout<<"        ��Ϸ����\n";
			break;
		}
		}while(1);
	return 0;
}
