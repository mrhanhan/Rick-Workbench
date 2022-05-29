//
// Created by rick on 2022/5/18.
//

#ifndef RICK_WORKBENCH_FILE_UTILS_H
#define RICK_WORKBENCH_FILE_UTILS_H
#define FILE_TEXT char *

#include <stdlib.h>
#define clear_file_text(FILE_TEXT) (free(FILE_TEXT))
/**
 * 读取文件
 * @param path 文件路径
 * @param content_buffer    内容Buffer
 * @return 1 读取失败 0 读取成功
 */
int read_all(const char* path, FILE_TEXT* content_buffer);

#endif //RICK_WORKBENCH_FILE_UTILS_H
