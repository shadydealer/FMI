#include <stdio.h>
#include <stack>


inline bool DFS(bool arr[1000][1000], int classes);

int main()
{

    int tests = 0;
    scanf("%d", &tests);

    int classes = 0;
    int parentId = 0;
    int inherits = 0;


    for(unsigned int i = 0; i < tests; ++i)
    {

        bool vertices[1000][1000] = {{false}};
        scanf("%d", &classes);

        for(unsigned int j = 0; j < classes; ++j)
        {
            scanf("%d", &inherits);
            for(unsigned int k = 0; k < inherits; ++k)
            {
                scanf("%d", &parentId);
                vertices[j][parentId-1] = true;
            }
        }

        /* for(unsigned int i = 0; i < classes; ++i)
        {
            for(unsigned int j = 0; j < 10; ++j)
            {
                printf("%d ", vertices[i][j]);
            }
            printf("\n");
        }
        */

        bool isDiamond = DFS(vertices, classes);

        printf("Case #%d: ", i + 1);

        if(isDiamond)
            printf("Yes");
        else
            printf("No");

        printf("\n");

         

    }

   return 0;
}

inline bool DFS(bool arr[1000][1000], int classes)
{
    std::stack<int> adj;
    bool colors[1000] = {false};
    
    unsigned int temp = 0;

    bool isRoot = true;

for(unsigned int i = 0; i < 1000; ++i)
{
    isRoot = true;
    
    for(unsigned int j = 0; j <1000; ++j)
    {
        if(arr[j][i])
            isRoot = false;
    }
    
    if(isRoot)
        adj.push(i);

    while(!adj.empty())
    {
        temp = adj.top();
        adj.pop();
        
        if(colors[temp])
            return true;

        colors[temp] = true;
        
        for(unsigned int j = 0; j <1000; ++j)
        {
            if(arr[j][temp])
                adj.push(j);
        }
    }
}
    return false;
}