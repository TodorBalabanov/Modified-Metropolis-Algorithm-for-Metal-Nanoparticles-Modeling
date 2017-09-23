#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

const int CENTER_OFFSET = 10;

const int CUBE_SPACE_SIZE = 21;

const int CUBE_GRID_SIZE = 2 * CUBE_SPACE_SIZE;

short grid[CUBE_GRID_SIZE][CUBE_GRID_SIZE][CUBE_GRID_SIZE];

const short EMPTY_CELL = 0;

const short SIMPLE_CUBIC = 1;

const short BODY_CENTERED_CUBIC = 2;

const short FACE_CENTERED_CUBIC = 3;

void clear() {
	for(int z=0; z<CUBE_GRID_SIZE; z++) {
		for(int y=0; y<CUBE_GRID_SIZE; y++) {
			for(int x=0; x<CUBE_GRID_SIZE; x++) {
				grid[x][y][z] = EMPTY_CELL;
			}
		}
	}
}

void addSimpleCubic() {
	for(int z=0; z<CUBE_GRID_SIZE; z+=2) {
		for(int y=0; y<CUBE_GRID_SIZE; y+=2) {
			for(int x=0; x<CUBE_GRID_SIZE; x+=2) {
				grid[x][y][z] = SIMPLE_CUBIC;
			}
		}
	}
}

void addBodyCenteredCubic() {
	for(int z=1; z<CUBE_GRID_SIZE; z+=2) {
		for(int y=1; y<CUBE_GRID_SIZE; y+=2) {
			for(int x=1; x<CUBE_GRID_SIZE; x+=2) {
				grid[x][y][z] = BODY_CENTERED_CUBIC;
			}
		}
	}
}

void addFaceCenteredCubic() {
	for(int z=1; z<CUBE_GRID_SIZE; z+=2) {
		for(int y=1; y<CUBE_GRID_SIZE; y+=2) {
			for(int x=0; x<CUBE_GRID_SIZE; x+=2) {
				grid[x][y][z] = FACE_CENTERED_CUBIC;
			}
		}
	}
	for(int z=1; z<CUBE_GRID_SIZE; z+=2) {
		for(int y=0; y<CUBE_GRID_SIZE; y+=2) {
			for(int x=1; x<CUBE_GRID_SIZE; x+=2) {
				grid[x][y][z] = FACE_CENTERED_CUBIC;
			}
		}
	}
	for(int z=0; z<CUBE_GRID_SIZE; z+=2) {
		for(int y=1; y<CUBE_GRID_SIZE; y+=2) {
			for(int x=1; x<CUBE_GRID_SIZE; x+=2) {
				grid[x][y][z] = FACE_CENTERED_CUBIC;
			}
		}
	}
}

const char CUBE_TEMPLATE[] = 
"   facet normal -1 0 0\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal -1 0 0\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 0 0 1\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 0 0 1\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 1 0 0\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 1 0 0\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 0 0 -1\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 0 0 -1\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 0 1 0\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 0 1 0\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 0 -1 0\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n"
"   facet normal 0 -1 0\r\n"
"      outer loop\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"         vertex %d %d %d\r\n"
"      endloop\r\n"
"   endfacet\r\n";

void save(const char *name) {
	FILE *file = fopen(name, "w");

	/*
	 * Start block.
	 */
	fprintf(file, "solid %s", name);
	fprintf(file, "\r\n");

	int delta = 0;
	int sides[6] = {0, 0, 0, 0, 0, 0};
	for(int z=0; z<CUBE_GRID_SIZE; z++) {
		for(int y=0; y<CUBE_GRID_SIZE; y++) {
			for(int x=0; x<CUBE_GRID_SIZE; x++) {
				if (grid[x][y][z] == EMPTY_CELL) {
					continue;
				} else {
					delta = grid[x][y][z];
				}

	sides[0] = CENTER_OFFSET + 0 - delta;
	sides[1] = CENTER_OFFSET + 0 + delta;
	sides[2] = CENTER_OFFSET + 0 - delta;
	sides[3] = CENTER_OFFSET + 0 + delta;
	sides[4] = CENTER_OFFSET + 0 - delta;
	sides[5] = CENTER_OFFSET + 0 + delta;

	/*
	 * Single cube.
	 */
	fprintf(file, CUBE_TEMPLATE, 
				sides[0], sides[3], sides[5],
				sides[0], sides[3], sides[4],
				sides[0], sides[2], sides[5],

				sides[0], sides[2], sides[5],
				sides[0], sides[3], sides[4],
				sides[0], sides[2], sides[4],
				
				sides[1], sides[3], sides[5],
				sides[0], sides[3], sides[5],
				sides[1], sides[2], sides[5],
				
				sides[1], sides[2], sides[5],
				sides[0], sides[3], sides[5],
				sides[0], sides[2], sides[5],
				
				sides[1], sides[3], sides[4],
				sides[1], sides[3], sides[5],
				sides[1], sides[2], sides[4],
				
				sides[1], sides[2], sides[4],
				sides[1], sides[3], sides[5],
				sides[1], sides[2], sides[5],
				
				sides[0], sides[3], sides[4],
				sides[1], sides[3], sides[4],
				sides[0], sides[2], sides[4],

				sides[0], sides[2], sides[4],
				sides[1], sides[3], sides[4],
				sides[1], sides[2], sides[4],
				
				sides[1], sides[3], sides[5],
				sides[1], sides[3], sides[4],
				sides[1], sides[3], sides[5],
				
				sides[0], sides[3], sides[5],
				sides[1], sides[3], sides[4],
				sides[0], sides[3], sides[4],
				
				sides[1], sides[2], sides[4],
				sides[1], sides[2], sides[5],
				sides[0], sides[2], sides[4],
				
				sides[0], sides[2], sides[4],
				sides[1], sides[2], sides[5],
				sides[0], sides[2], sides[5]
	);
			}
		}
	}

	/*
	 * End block.
	 */
	fprintf(file, "endsolid %s", name);
	fprintf(file, "\r\n");

	fclose(file);
}

int main() {
	clear();
	addSimpleCubic();
	addBodyCenteredCubic();
	addFaceCenteredCubic();
	save("out.stl");

	return(EXIT_SUCCESS);
}
