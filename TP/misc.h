/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   misc.h
 * Author: FNAC
 *
 * Created on 19 de abril de 2021, 13:26
 */

#ifndef MISC_H
#define MISC_H

#ifdef __cplusplus
extern "C" {
#endif

    int check_empty(FILE *file);
    void clear_newlines(void);
    void clearScreen(void);
    void header(void);
    void PressEnterToContinue(void);


#ifdef __cplusplus
}
#endif

#endif /* MISC_H */

