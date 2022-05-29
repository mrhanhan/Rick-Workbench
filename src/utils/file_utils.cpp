//
// Created by rick on 2022/5/18.
//

#include "file_utils.hpp"
#include <stdlib.h>
#include <stdio.h>

/**
 * 读取文件
 * @param path 文件路径
 * @param content_buffer    内容Buffer
 * @return 1 读取失败 0 读取成功
 */
int read_all(const char* path, FILE_TEXT* content_buffer) {
    FILE * fs = fopen(path, "r");
    if (!fs) {
        return 1;
    }
    // 获取文件大小
    fseek(fs, 0, SEEK_END);
    long file_size = ftell(fs);
    // 恢复到初始位置
    fseek(fs, 0, SEEK_SET);
    *(content_buffer) = static_cast<char *>(calloc(file_size, sizeof(char)));
    // 读取文件内存
    fread(*(content_buffer), sizeof(char), file_size, fs);
    // Close
    fclose(fs);
    return 0;
}