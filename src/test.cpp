# include <iostream>

int main() {
    float vertexes[] = {
            .0f, .5f, .0f,  1.0f, .0f, .0f,
            .5f, -.5f, .0f, .0f, 1.0f, .0f,
            -.5f, -.5f, .0f, .0f, .0f, 1.0f,
    };
    char * a = (char*)malloc(100);
    float *p = vertexes;
    std::cout << sizeof(vertexes) << std::endl;
    std::cout << sizeof(*p) << std::endl;
    std::cout << sizeof(*a) << std::endl;
    free(a);
    return 0;
}