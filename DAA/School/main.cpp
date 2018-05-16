#include <stdio.h>
#include <queue>

void delete_2d_matrix(bool ** matrix, unsigned short dimensions);
bool ** build_2d_matrix(unsigned short dimensions);
void print_2d_matrix(bool ** matrix, unsigned short dimensions);
const unsigned short get_connected_component_count(bool ** matrix, unsigned short dimensions);

int main()
{
    unsigned short n = 0, m = 0;
    scanf("%hu %hu", &n, &m);
    
    unsigned short lStudent = 0, rStudent = 0;

    bool ** matrix = build_2d_matrix(n);

    for(unsigned short line = 0; line < m; ++line)
    {
        scanf("%hu %hu", &lStudent, &rStudent);
        lStudent -=1;
        rStudent -=1;
        matrix[lStudent][rStudent] = true;
        matrix[rStudent][lStudent] = true;
    }
    /*  
    print_2d_matrix(matrix, n);
     */
    unsigned short components = get_connected_component_count(matrix, n);

    printf("%u\n", components);

    delete_2d_matrix(matrix, n);
    return 0;
}

bool ** build_2d_matrix(unsigned short dimensions)
{
    bool ** matrix = new bool*[dimensions];

    for(unsigned short row = 0; row < dimensions; ++row)
        matrix[row] = new bool[dimensions]{false};

    return matrix;
}

void delete_2d_matrix(bool ** matrix, unsigned short dimensions)
{
    for (unsigned short row = 0; row < dimensions; ++ row)
        delete[] matrix[row];
    
    delete[] matrix;
}

void print_2d_matrix(bool ** matrix, unsigned short dimensions)
{
    for (unsigned short row = 0; row < dimensions; ++ row)
    {
        for (unsigned short col = 0; col < dimensions; ++col)
            printf("%u ", matrix[col][row]);
        
        printf("\n");
    }
}

const unsigned short get_connected_component_count(bool ** matrix, unsigned short dimensions)
{
    unsigned short components = 0;

    bool * vertColors = new bool[dimensions]{false};
    std::queue<unsigned int> adjQueue;

    unsigned int currVert = 0;

    for(unsigned int vert = 0; vert < dimensions; ++ vert)
    {
        if(!vertColors[vert])
        {
            ++components;

            for(unsigned int adjVert = 0; adjVert < dimensions; ++ adjVert)
            {
                if(matrix[vert][adjVert])
                    adjQueue.push(adjVert);
            }       

            while(!adjQueue.empty())
            {
                currVert = adjQueue.front(); 
                adjQueue.pop();
                vertColors[currVert] = true;

                for(unsigned int adjVert = 0; adjVert < dimensions; ++ adjVert)
                {
                    if(matrix[currVert][adjVert]
                    && !vertColors[adjVert])
                        adjQueue.push(adjVert);
                }   
            }
        }

    }
    delete[] vertColors;
    return components;
}