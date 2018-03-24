#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct{
	char c[10];
}color;

// Nhập dữ liệu của đồ thị
int* inputTree(int& n, int& m){
	FILE* FileIn;
	FileIn = fopen("input7.txt", "r");
	fscanf(FileIn, "%d%d", &n, &m);
	int* b = (int*)malloc(2*m*sizeof(int));
	for(int i = 0; i < m; i++){
		fscanf(FileIn, "%d%d", &b[2*i], &b[2*i+1]);
	}
	fclose(FileIn);

	return b;
}

// Lấy bậc các đỉnh của đồ thị
int getDegreeOfGraph(int* b, int m, int n, int* Deg, int* Degmax){
	int tmp;
	for(int i = 0; i < m; i++){
		tmp = b[2*i];
		Deg[tmp]++;
		tmp = b[2*i+1];
		Deg[tmp]++;
	}

	// Tìm đỉnh có bậc <= k-1, cụ thể tìm đỉnh có bậc k-1 và tìm giá trị bậc max
	*Degmax = 0;
	for(int j = n-1; j >= 0 ; j--){
		for(int i = 1; i <= n; i++){
			if( (j == Deg[i]) && (*Degmax < j) ){
				*Degmax = Deg[i];
			}
			if( (j == Deg[i]) && (j < *Degmax) ){
				return i;
			}
		}
	}
}

// Kiểm tra tính chính quy của đồ thị
bool checkRegularGraph(int* Deg, int n){
	for(int i = 1 ; i < n; i++){
		if(Deg[i] != Deg[i+1]){
			return false;
		}
	}
	return true;
}

// Kiểm tra tính liên thông của đồ thị
bool checkInterconnectedGraph(int* a, int m, int n){
	int* Tick = (int*)malloc( (n+1)*sizeof(int) );
	
	for(int i = 1; i <= n+1; i++){
		Tick[i] = 0;
	}

	int tmp = a[0], count = 0;
	Tick[tmp] = 1;
	count++;

	for(int i = 0; i < m; i++){
		for(int j = 0; j < m; j++){
			int x = a[2*j], y = a[2*j+1];
			if( Tick[x] == 1 && Tick[y] == 0 ){
				tmp = a[2*j+1];
				Tick[tmp] = 1;
				count++;
			}
			else if( Tick[y] == 1 && Tick[x] == 0 ){
				tmp = a[2*j];
				Tick[tmp] = 1;
				count++;
			}
			if(count == n){
				return true;
			}
		}
	}

	return false;
}

// Sắp xếp thứ tự các đỉnh để tô màu
int* sort(int* b, int m, int n, int Indexdegmax2){
	int* tmp = (int*)malloc(n*sizeof(int));

	tmp[0] = Indexdegmax2;
	int k = 1, h = 0;					// k: chỉ số mảng sort				 h : chỉ số đỉnh liên kết với các đỉnh sau nó

	for(int j = 0; j < m; j++){
		for(int i = 0; i < m; i++){
			if(tmp[h] == b[2*i]){
				tmp[k] = b[2*i+1];
				k++;
				b[2*i] = b[2*i+1] = 0;
			}
			else if(tmp[h] == b[2*i+1]){
				tmp[k] = b[2*i];
				k++;
				b[2*i] = b[2*i+1] = 0;
			}
		}
		// Xóa bỏ cạnh mà các phần tử đã xuất hiện trong dãy sắp xếp
		for(int i = 0; i < m; i++){
			int x = 0, y = 0;
			for(int l = 0; l < k; l++){
				if(b[2*i] == tmp[l]){
					x = 1;
				}
			}
			if(x == 1){
				for(int l = 0; l < k; l++){
					if(b[2*i+1] == tmp[l]){
						y = 1;
					}
				}
			}
			if( (x == 1) && (y == 1) ){
				b[2*i] = b[2*i+1] = 0;
			}
		}
		if(k == n){
			return tmp;
		}
		h++;
	}
}

// Tô màu đồ thị liên thông và không chính quy
void paintTheGraph(int* a, int m, int n, int* Sorted, int* Indexcolor){
	Indexcolor[Sorted[0]] = 1;
	for(int i = 1; i < n; i++){
		int paint = 1, tmp = 0;
		while(paint != tmp){
			tmp = paint;
			for(int j = 0; j < m; j++){
				if(Sorted[i] == a[2*j]){
					if(Indexcolor[a[2*j+1]] == paint){
						paint++;
					}
				}
				else if(Sorted[i] == a[2*j+1]){
					if(Indexcolor[a[2*j]] == paint){
					paint++;
					}
				}
			}
		}
		Indexcolor[Sorted[i]] = paint;
	}
}

// In ra đồ thị ở dang ngôn ngữ DOT
void outputGraph(int* a, int m, int n, int* Indexcolor,  color* COLOR){
	FILE* FileOut;
	FileOut = fopen("GP.dot", "w");

	fprintf(FileOut, "\ngraph GraphPainted\n{\n");
	for(int i = 1; i < n+1; i++){
		fprintf(FileOut, "\t%d [fillcolor=%s, style=filled];\n", i, COLOR[Indexcolor[i]-1].c);
	}
	for(int i = 0; i < m; i++){
		fprintf(FileOut, "\t%d -- %d\n", a[2*i], a[2*i+1]);
	}
	fprintf(FileOut, "}");

	fclose(FileOut);
}


int main()
{
	int n, m, Degmax, Indexdegmax2;										// n: Số đỉnh	m: Số cạnh

	int* a = inputTree(n, m);
	int* b = inputTree(n, m);											// Tạo mảng copy của a

	int* Deg = (int*)malloc((n+1)*sizeof(int));							// Mảng chứa bậc của các đỉnh
	for(int i = 0; i < n+1; i++){										// Khởi tạo số bậc của các đỉnh
		Deg[i] = 0;
	}

	Indexdegmax2 = getDegreeOfGraph(b, m, n, Deg, &Degmax);	// Lấy chỉ số phần tử có bậc k-1 (đồ thị liên thông và không chính quy) và bậc max cho tô màu

	// Nhập tên màu vào mảng chứa tên màu
	color* COLOR = (color*)malloc((16)*sizeof(color));      // Có bao nhiêu màu thì cấp phát bấy nhiêu ô nhớ (dùng Degmax+1 ô nhớ cho cách lấy màu thứ 2)
	strcpy(COLOR[0].c, "red");
	strcpy(COLOR[1].c, "green");
	strcpy(COLOR[2].c, "blue");
	strcpy(COLOR[3].c, "yellow");
	strcpy(COLOR[4].c, "pink");
	strcpy(COLOR[5].c, "orange");
	strcpy(COLOR[6].c, "gray");
	strcpy(COLOR[7].c, "brown");
	strcpy(COLOR[8].c, "beige");
	strcpy(COLOR[9].c, "violet");
	strcpy(COLOR[10].c, "darkgreen");
	strcpy(COLOR[11].c, "purple");
	strcpy(COLOR[12].c, "gold");
	strcpy(COLOR[13].c, "greenyellow");
	strcpy(COLOR[14].c, "khaki3");
	strcpy(COLOR[15].c, "indianred1");

	//FILE* FileIn;													// Cách lấy màu thứ 2 là đọc màu từ file
	//FileIn = fopen("COLOR.txt", "r");
	//for(int i = 0; i < Degmax+1; i++){
	//	fflush(stdin);
	//	fscanf(FileIn, "%s", &COLOR[i].c);
	//}
	//fclose(FileIn);

	
	
	bool checkRG = checkRegularGraph(Deg, n);				// Kiểm tra tính chính quy của đồ thị
	bool checkIG = checkInterconnectedGraph(a, m, n);	    // Kiểm tra tính liên thông của đồ thị	


	// TÔ MÀU ĐỒ THỊ
	if( (checkRG == false) && (checkIG == true) ){
		// Sắp xếp thứ tự tô màu các đỉnh
		int* Sorted = sort(b, m, n, Indexdegmax2);				// Mảng chứa các đỉnh đã sắp thứ tự để tô màu
		free(b);

		int* Indexcolor = (int*)malloc((n+1)*sizeof(int));		// Khởi tạo mảng chứa chỉ số tương ứng chỉ số màu
		for(int i = 0; i < n+1; i++){
			Indexcolor[i] = 0;
		}

		paintTheGraph(a, m, n, Sorted, Indexcolor);			// Lấy chỉ số màu của đỉnh
		free(Sorted);

		outputGraph(a, m, n, Indexcolor, COLOR);			// Xuất ra file dạng ngôn ngữ dot kèm tên màu
		free(Indexcolor);

	}
	else if( (checkIG == false) || (checkRG == true)){
			// Sắp xếp thứ tự tô màu các đỉnh
			int* Sorted = (int*)malloc((n+1)*sizeof(int));		// Mảng chứa các đỉnh đã sắp thứ tự để tô màu
			for(int i = 0; i < n; i++){
				Sorted[i] = i+1;
			}

			int* Indexcolor = (int*)malloc((n+1)*sizeof(int));		// Khởi tạo mảng chứa chỉ số tương ứng chỉ số màu
			for(int i = 0; i < n+1; i++){
				Indexcolor[i] = 0;
			}

			paintTheGraph(a, m, n, Sorted, Indexcolor);				// Lấy chỉ số màu của đỉnh
			free(Sorted);

			outputGraph(a, m, n, Indexcolor, COLOR);				// Xuất ra file dạng ngôn ngữ dot kèm tên màu
			free(Indexcolor);
	}

	//getch();
	return 0;
}
