#include <iostream>
#include <fstream>
#include "stack.h"
#include "graph.h"
using namespace std;
/*                Дискретная оптимизация
* Определить, является ли данный связный  неориентированный  граф  двудольным.
* Метод решения: Поиск в глубину.
* Музафаров Максим МТ-408
*********************************************************************************/
bool fdepth(apex* graf, int m, int v, int* color_apex)
{
	apex *current_apex=new apex; //текущая вершина
	int kv=0; //количество вершин
	tknot* tasks; 
	new_null(tasks); //пустой стек задач
	int* seen_apex=new int [m]; //массив просмотренных вершин
	current_apex->n=v; //кладем первую вершину в список задач
	current_apex->next=graf[current_apex->n].next; //со ссылкой на первую смежную.
	add_compon(tasks, *current_apex); //добавляем задание с первой вершиной в стек задач
	for(int i=0; i<m; i++) seen_apex[i]=color_apex[i]=0; //все вершины считаем непросмотренными
	seen_apex[kv++]=current_apex->n; //в список просмотренных вершин добавляем текущую, увеличивая количество просмотренных
	apex *t; //курсор для прохождения списка смежных вершин
	int color=1; //цвет текущей вершины
	color_apex[v]=color;
	while (!check_empty(tasks)) //пока есть задачи выполняем
	{   read_compon(tasks, *current_apex); //читаем задачу
	color=color_apex[current_apex->n];
	t=current_apex->next; //ставим курсор на первую смежную
	bool fl=color_apex[t->n]>0; //флаг, просмотрена ли вершина ранее
	if(fl)
	{	
		t=t->next;
		while(t &&(color_apex[t->n]>0)) //пробегаем список смежности пока не встретим непросмотренную
		{ if (color_apex[t->n]==color) return false;	//Если нашли смежную того же цвета - не двудольный.			
		t=t->next; 
		}
		if (t) 
		{	del_compon(tasks); //если смотрели, то удаляем задачу из стека
		current_apex->next=t; //если непросмотренную нашли - добавляем её в стек задач
		add_compon(tasks, *current_apex);
		}
		else 	del_compon(tasks);
	}
	else //если же вершина не просмотрена, то:
	{
		current_apex->n=t->n; //создаем задачу 
		current_apex->next=graf[current_apex->n].next;
		add_compon(tasks, *current_apex); //и добавляем в стек
		color=color==1?2:1; //меняем цвет
		color_apex[t->n]=color; //красим вершину
		seen_apex[kv++]=current_apex->n; //добавляем к просмотренным
	}
	}
	return true;
}
const int maxn=20;
int main()
{
	//Входной и выходной файлы
	ifstream fi("in.txt");
	ofstream fo("out.txt");
	//Граф
	apex graf[maxn];
	int m;
	//Чтение графа
	readgraf (fi,graf,m);
	int v=0;
	bool dvudol;
	int* color_apex=new int [m]; //цвет вершины (0 - не просмотрена, 1, 2)
	dvudol=fdepth(graf,m,v,color_apex);
	if (dvudol) 
	{fo<<"Y\n";
	char color=color_apex[0];
	for (int i=0;i<m;i++) if (color_apex[i]==color) fo<<i+1<<" ";
	fo<<"0\n";
	color=color==1?2:1;
	for (int i=0;i<m;i++) if (color_apex[i]==color) fo<<i+1<<" ";
	}
	else fo<<"N";
	fi.close();
	fo.close();
	return 0;
}