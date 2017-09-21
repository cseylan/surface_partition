/*
Generates cube whose each side varies between [-1, 1] 
Output is in .off format.

Last modified: 24.08.2017 
Author: Caglar Seylan
*/

#include <cstdio>
#include <cstdlib>
#include <Eigen/Dense>
#include <vector>

using namespace Eigen;
using namespace std;

int N;	// Number of 'cells' for each edge of the cube
int **vertexMap[6];

struct Vertex
{
	int id;
	Vector3f point;

	Vertex(int id, Vector3f point)
	{
		this->id = id;
		this->point = point;
	}
};

struct Triangle
{
	int v1;
	int v2;
	int v3;

	Triangle(int v1, int v2, int v3)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}
};

// Takes vertices v1 and v2 on the cube corners and fills the edge between with N-1 vertices.
// v1 is at left, v2 is at right. 
void addEdgeVertices(int v1, int v2, vector<Vertex> & vertexList)
{
	float stepLength = 2.0 / N; // Length of one side of the grid
	int M = N - 1;	// # of vertices in between

	for(int i = 0 ; i < M ; i++)
	{
		Vector3f newPoint = vertexList[v1].point + (vertexList[v2].point - vertexList[v1].point).normalized() * (i + 1) * stepLength;

		vertexList.push_back(*(new Vertex(vertexList.size(), newPoint)));
	}

}

// Takes diagonal vertices of a face of a cube and fills the face with (N-1)^2 vertices.
// v1 is at top left, v2 is at bottom left, v3 is at bottom right, v4 is at top right.
void addFaceVertices(int v1, int v2, int v3, int v4, vector<Vertex> & vertexList)
{
	float stepLength = 2.0 / N;
	int M = N - 1;
	Vector3f x_dir = (vertexList[v4].point - vertexList[v1].point).normalized();
	Vector3f y_dir = (vertexList[v2].point - vertexList[v1].point).normalized();

	for(int i = 0 ; i < M ; i++)
		for(int j = 0 ; j < M ; j++)
		{
			Vector3f newPoint = vertexList[v1].point + (j + 1) * stepLength * x_dir + (i + 1) * stepLength * y_dir;

			vertexList.push_back(*(new Vertex(vertexList.size(), newPoint)));
		}
}

int main(void)
{
	vector<Vertex> vertexList;
	vector<Triangle> triangleList;

	scanf("%d", &N);

	for(int i = 0 ; i < 6 ; i++)
	{
		vertexMap[i] = (int **) malloc(sizeof(int *) * (N + 1));

		for(int j = 0 ; j < N + 1 ; j++)
			vertexMap[i][j] = (int *) malloc(sizeof(int) * (N + 1));
	}

	vertexList.push_back(*(new Vertex(0, Vector3f(-1, -1, 1))));	// vertex 0 -> (-1, -1, 1)
	vertexList.push_back(*(new Vertex(1, Vector3f(1, -1, 1))));		// vertex 1 -> (1, -1, 1)
	vertexList.push_back(*(new Vertex(2, Vector3f(1, 1, 1))));		// vertex 2 -> (1, 1, 1)
	vertexList.push_back(*(new Vertex(3, Vector3f(-1, 1, 1))));		// vertex 3 -> (-1, 1, 1)
	vertexList.push_back(*(new Vertex(4, Vector3f(-1 ,-1 ,-1))));	// vertex 4 -> (-1, -1, -1)
	vertexList.push_back(*(new Vertex(5, Vector3f(1, -1, -1))));	// vertex 5 -> (1, -1, -1)
	vertexList.push_back(*(new Vertex(6, Vector3f(1, 1, -1))));		// vertex 6 -> (1, 1, -1)
	vertexList.push_back(*(new Vertex(7, Vector3f(-1, 1, -1))));	// vertex 7 -> (-1, 1, -1)

	addEdgeVertices(0, 1, vertexList);	// 0
	addEdgeVertices(1, 2, vertexList);	// 1
	addEdgeVertices(2, 3, vertexList);	// 2
	addEdgeVertices(3, 0, vertexList);	// 3
	addEdgeVertices(0, 4, vertexList);	// 4
	addEdgeVertices(1, 5, vertexList);	// 5
	addEdgeVertices(2, 6, vertexList);	// 6
	addEdgeVertices(3, 7, vertexList);	// 7
	addEdgeVertices(4, 5, vertexList);	// 8
	addEdgeVertices(5, 6, vertexList);	// 9
	addEdgeVertices(6, 7, vertexList);	// 10
	addEdgeVertices(7, 4, vertexList);	// 11

	addFaceVertices(0, 1, 2, 3, vertexList);	// 0
	addFaceVertices(0, 4, 5, 1, vertexList);	// 1
	addFaceVertices(1, 5, 6, 2, vertexList);	// 2
	addFaceVertices(2, 6, 7, 3, vertexList);	// 3
	addFaceVertices(3, 7, 4, 0, vertexList);	// 4
	addFaceVertices(6, 5, 4, 7, vertexList);	// 5

	// Prepare the vertex map.

	vertexMap[0][0][0] = 0;
	vertexMap[0][0][N] = 3;
	vertexMap[0][N][0] = 1;
	vertexMap[0][N][N] = 2;

	vertexMap[1][0][0] = 0;
	vertexMap[1][0][N] = 1;
	vertexMap[1][N][0] = 4;
	vertexMap[1][N][N] = 5;

	vertexMap[2][0][0] = 1;
	vertexMap[2][0][N] = 2;
	vertexMap[2][N][0] = 5;
	vertexMap[2][N][N] = 6;

	vertexMap[3][0][0] = 2;
	vertexMap[3][0][N] = 3;
	vertexMap[3][N][0] = 6;
	vertexMap[3][N][N] = 7;

	vertexMap[4][0][0] = 3;
	vertexMap[4][0][N] = 0;
	vertexMap[4][N][0] = 7;
	vertexMap[4][N][N] = 4;

	vertexMap[5][0][0] = 6;
	vertexMap[5][0][N] = 7;
	vertexMap[5][N][0] = 5;
	vertexMap[5][N][N] = 4;

	for(int i = 1 ; i < N ; i++)
	{
		vertexMap[0][i][0] = vertexList[7 + i].id;
		vertexMap[0][N][i] = vertexList[7 + (N - 1) + i].id;
		vertexMap[0][N - i][N] = vertexList[7 + (N - 1) * 2 + i].id;
		vertexMap[0][0][N - i] = vertexList[7 + (N - 1) * 3 + i].id;

		vertexMap[1][i][0] = vertexList[7 + (N - 1) * 4 + i].id;
		vertexMap[1][N][i] = vertexList[7 + (N - 1) * 8 + i].id;
		vertexMap[1][i][N] = vertexList[7 + (N - 1) * 5 + i].id;
		vertexMap[1][0][i] = vertexList[7 + i].id;

		vertexMap[2][i][0] = vertexList[7 + (N - 1) * 5 + i].id;
		vertexMap[2][0][i] = vertexList[7 + (N - 1) + i].id;
		vertexMap[2][N][i] = vertexList[7 + (N - 1) * 9 + i].id;
		vertexMap[2][i][N] = vertexList[7 + (N - 1) * 6 + i].id;

		vertexMap[3][0][i] = vertexList[7 + (N - 1) * 2 + i].id;
		vertexMap[3][N][i] = vertexList[7 + (N - 1) * 10 + i].id;
		vertexMap[3][i][0] = vertexList[7 + (N - 1) * 6 + i].id;
		vertexMap[3][i][N] = vertexList[7 + (N - 1) * 7 + i].id;

		vertexMap[4][0][i] = vertexList[7 + (N - 1) * 3 + i].id;
		vertexMap[4][N][i] = vertexList[7 + (N - 1) * 11 + i].id;
		vertexMap[4][i][0] = vertexList[7 + (N - 1) * 7 + i].id;
		vertexMap[4][i][N] = vertexList[7 + (N - 1) * 4 + i].id;

		vertexMap[5][0][i] = vertexList[7 + (N - 1) * 10 + i].id;
		vertexMap[5][N][N - i] = vertexList[7 + (N - 1) * 8 + i].id;
		vertexMap[5][N - i][0] = vertexList[7 + (N - 1) * 9 + i].id;
		vertexMap[5][i][N] = vertexList[ 7 + (N - 1) * 11 + i].id; 
	}

	int offset = 8 + (N - 1) * 12;

	for(int i = 1 ; i < N ; i++)
		for(int j = 1 ; j < N ; j++)
		{
			vertexMap[0][i][j] = vertexList[offset + (i - 1) * (N - 1) + j - 1].id;
			vertexMap[1][i][j] = vertexList[offset + (N - 1) * (N - 1) + (i - 1) * (N - 1) + j - 1].id;
			vertexMap[2][i][j] = vertexList[offset + (N - 1) * (N - 1) * 2 + (i - 1) * (N - 1) + j - 1].id;
			vertexMap[3][i][j] = vertexList[offset + (N - 1) * (N - 1) * 3 + (i - 1) * (N - 1) + j - 1].id;
			vertexMap[4][i][j] = vertexList[offset + (N - 1) * (N - 1) * 4 + (i - 1) * (N - 1) + j - 1].id;
			vertexMap[5][i][j] = vertexList[offset + (N - 1) * (N - 1) * 5 + (i - 1) * (N - 1) + j - 1].id;
		}

	for(int k = 0 ; k < 6 ; k++)
		for(int i = 0 ; i < N ; i++)
			for(int j = 0 ; j < N ; j++)
			{
				int v1 = vertexMap[k][i][j];
				int v2 = vertexMap[k][i][j + 1];
				int v3 = vertexMap[k][i + 1][j];
				int v4 = vertexMap[k][i + 1][j + 1];

				triangleList.push_back(*(new Triangle(v1, v4, v2)));
				triangleList.push_back(*(new Triangle(v1, v3, v4)));
			}

	FILE *pFile = fopen("syntetic_cube.off", "w");

	fprintf(pFile, "OFF\n");
	fprintf(pFile, "%lu %lu 0\n", vertexList.size(), triangleList.size());
	for(int i = 0 ; i < vertexList.size() ; i++)
		fprintf(pFile, "%f %f %f\n", vertexList[i].point(0), vertexList[i].point(1), vertexList[i].point(2));
	for(int i = 0 ; i < triangleList.size() ; i++)
		fprintf(pFile, "3 %d %d %d\n", triangleList[i].v1, triangleList[i].v2, triangleList[i].v3);

	fclose(pFile);
	/*
	for(int k = 0 ; k < 6 ; k++)
	{
		for(int i = 0 ; i <= N ; i++)
		{
			for(int j = 0 ; j <= N ; j++)
				printf("%d ", vertexMap[k][i][j]);
			printf("\n");
		}
		printf("---------------------------------\n");
	}
	*/

	/*
	for(int i = 0 ; i < vertexList.size() ; i++)
		printf("%d - %f %f %f\n", vertexList[i].id, vertexList[i].point(0), vertexList[i].point(1), vertexList[i].point(2));
	*/

	return 0;
}
