int outmat(int a[], int n, int m);
int inmat(int a[],int n,int m);
string writemat(int a[], int n, int m);
int readmat(int a[],int n,int m,string str);
int edmat(int a[],int n,int m);
int proverka(int vecn[],int n, int N, unsigned int m, int k[], int size); 
int outvec(unsigned char a, int i);
int invec(unsigned char& a, int i);
string perebor(int vecn[],int n1, int n, int k[], int size, unsigned char options);
int summat(int vecn[],int k[], int n, int size);

int mainwork (string& main_string, unsigned char options)
{
	int k[100],n,m,vecn[100],zsize;
	istringstream iss(main_string);
	iss >> n; // Читаем ширину-высоту
	iss >> m;
	
	for(int b=0,a=0,i=0;main_string[i]!=0;i++) // Стираем их из строки
	{
		if (a>1) main_string[i-b-a]=main_string[i];
		else
		{
			if ((main_string[i]==10)||(main_string[i]==13)||(main_string[i]==32)) a++;
			else b++;
		}
		zsize=i-b-a+1;
	}
	main_string[zsize]=0;
	if (options>>1&1) edmat(k,n,m);
	else readmat(k,n,m,main_string);
	if (!(options>>2&1)) main_string=writemat(k,n,m);
	else
	{
		main_string="";
		for(int i=1;i<m+1;i++) 
		{
		main_string=main_string+perebor(vecn,i,m,k,n,options);
		if ((!(options>>3&1))&&(main_string!="")) i=m+1;
		}
	}
	return 0;
}

int summat(int vecn[],int k[], int n, int size) // Суммирует полученные строки по номерам.
// Где vecn - вектор с номерами, k - бинарная матрица, n - кол-во ед.(кол-во номеров)
{
	int x=0;
	for(int i=0;i<n;i++)
	{
	x=x|k[vecn[i]];
	}
	//outvec(x,size);
	return x;
}

int outmat(int a[], int n, int m) // Вывод бинарной матрицы
{
	for(int j=0;j<m;j++)
	{
		for(int i=n-1;i>-1;i--)
		{
			cout<<((a[j]>>i)&1);
		}
		cout<<'\n';
	}
	return 0;
}

int inmat(int a[],int n,int m) // Ввод бинарной матрицы
{
	char c;
	int g=0;
	
	for(int j=0;j<m;j++)
	{
		a[j]=0;
		for(int i=n;i>0;i--)
		{
			c=cin.get();
			//cout<<"j="<<j<<" i="<<i<<" c="<<c<<" g="<<g<<'\n';
			if((c==10)||(c==32)||(c==13)||(c==9)||(c==11)||(c==12)) {i++; g++;}
			else if(c!='0') a[j]=a[j]|(1<<i-1);
		}
		//outvec(a[j],10);
	}
	return 0;
}

string writemat(int a[], int n, int m) // Вывод бинарной матрицы
{
	int x;
	string s,str;
	str="";
	for(int j=0;j<m;j++)
	{
		for(int i=n-1;i>-1;i--)
		{
			x=((a[j]>>i)&1);
			ostringstream oss;
			oss<<x;
			s = oss.str();
			str=str+s;
		}
		str=str+'\n';
	}
	return str;
}

int readmat(int a[],int n,int m,string str) // Ввод бинарной матрицы
{
	char c;
	int g=0;
	
	for(int j=0;j<m;j++)
	{
		a[j]=0;
		for(int i=n;i>0;i--)
		{
			c=str[((j*(n))+(n-i+g))];
			//cout<<"j="<<j<<" i="<<i<<" c="<<c<<" g="<<g<<'\n';
			if((c==10)||(c==32)||(c==13)||(c==9)||(c==11)||(c==12)) {i++; g++;}
			else if(c!='0') a[j]=a[j]|(1<<i-1);
		}
		//outvec(a[j],10);
	}
	return 0;
}

int edmat(int a[],int n,int m) // Еденичная матрица с полной заменой (см. на 4 строки вниз)
{
	for(int j=0;j<m;j++)
	{	
		a[j]=0;
		for(int i=0;i<n+1;i++)
		{
			a[j]=((i-1)==j)?(a[j]|(1<<(n-i))):(a[j]);
		}
	}
	return a[100];
}

int proverka(int vecn[], int n, int N, unsigned int m, int k[], int size)
{
	// Перевод бинарного вектора в числовой с номерами едениц.
	int b, a=0;
	for(int i=N-1;a!=n;i--)
	{
		if ((m>>i)&1) 
		{
		vecn[a]=(N-1-i);
		a++;
		}
	}
	// Сложение
	a=summat(vecn,k,n,size);
	b=0;
	for (int i=size-1;i>-1;i--){b=b|(1<<i);} // Шаблон покрытия
	// Условие успеха
	if (a==b)
	{
		/*cout<<"Успех при "<<n<<"х строк. Это строки: ";
		for(int i=0;i<n;i++)
			{		
			cout<<vecn[i]<<' ';
			}
		cout<<'\n'; */
		return 1;
	}
	//outvec(a,size);
	//outvec(b,size);
	return 0;
}

int outvec(unsigned char a, int i) // Вывод бинарного вектора
{
	for(i=i-1;i>-1;i--)
	{
		cout<<((a>>i)&1);
	}
	cout<<'\n';
	return 0;
}

int invec(unsigned char& a, int i) // Ввод бинарного вектора
{
	char c;
	for(i=i-1;i>-1;i--)
	{
		c=cin.get();
		if ((c=='0')||(c=='1')) 
		{
			if(c=='0') a=a&(~(1<<i));
			else a=a|(1<<i);
		}
		else
		{
		a=a>>(i+1);
		i=-1;
		}
	}
	return 0;
}

string perebor(int vecn[],int n1, int n, int k[], int size, unsigned char options) // Перебрать все варианты с данным кол-вом 1-чек
// Где n1 - текущее кол-во 1-ек (Попытка на такое кол-во строк в покрытии)
// n - Общее кол-во возможных элементов (Общее кол-во строк)
{
	int sum,a,stop,n2,p;
	unsigned int z,m;
	string str="",s="";
	z=0;
	sum=1;
	m=0;
	n2=n1;
	ostringstream oss;
	// Защита от дурака.
	if ((n1>n)||(n1<0)) {cout<<"n1 не входит в рамки, оно равно "<<n1; return "";}
	// Генерируем вектор с 1 ками в начале. С него мы начинаем движение.
	for (int i=n-1;n1>0;n1--,i--){m=m|(1<<i);}
	n1=n2;
	// Генерируем вектор с 1 ками в конце. Он прерывает основной цикл.
	for (int i=0;n1>0;n1--,i++){z=z|(1<<i);}
	n1=n2;
	// Проверка для начального вектора
	if (proverka(vecn,n1,n,m,k,size))
	{
		ostringstream oss;
		oss<<n1;
		s = oss.str();
		if (options>>4&1) str=str+"Покрытие при количестве "+s+"х строк. Это строки: ";
		for(int i=0;i<n1;i++)
			{
			vecn[i]++;
			ostringstream oss;
			oss<<vecn[i];
			s = oss.str();
			str=str+s+' ';
			}
		str=str+'\n';
	}
	//outvec(m);
	// Основной цикл. Повторяет цикл перемещения, запускает проверку.
	for(int j=0; m!=z; j++, sum++)
	{
		// Цикл перемещения единичек по заданым условиям.
		// Что-то типа:
		// 11100
		// 11010
		// 11001
		// 10110
		// 10101
		// 10011
		// 01110
		// 01101
		// 01011 ... и т.д.
		p=0; a=1; stop=0;
		for(int i=0;((stop==0)&&(i<n));)
		{
			if((m>>i)&1) // Текущий эл.==1?
			{	
				if (a!=1) // До него были нули?
				{
				m=m|(1<<i-1);	// Cдвигаем 1-ку вправо
				m=m&(~(1<<i));
				for(;p!=0;i--,m=m|(1<<i-1),p--); // Если стирали 1-ки, возвращаем.
				stop=1; // Передых, для выдачи вектора.
				}
				else {p++;m=m&(~(1<<i));i++;} // Ставим 0, запоминаем это.
			}
			else {a=0;i++;} // Запомнили, что посетили нуль.
		}
		// Проверка для текущего вектора.
		if (proverka(vecn,n1,n,m,k,size))
		{
			ostringstream oss;
			oss<<n1;
			s = oss.str();
			if (options>>4&1) str=str+"Покрытие при количестве "+s+"х строк. Это строки: ";
			for(int i=0;i<n1;i++)
				{
				vecn[i]++;
				ostringstream oss;
				oss<<vecn[i];
				s = oss.str();
				str=str+s+' ';
				}
			str=str+'\n';
		}
		//outvec(m);
	}
	
	//cout<<"Всего вариантов: "<<sum<<'\n';
	return str;
}
