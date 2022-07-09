#include <stdio.h>
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <sysinfoapi.h>
#include <malloc.h>
#include <iostream>
#include <string>
#include <thread>
using namespace std;

int camX, camY;
POINT mouse;

#include "keys.h"
#include "string.h"
#include "window.h"
#include "varinit.h"
#include "stalker.h"

MSG WndMessage;
keybord mainkb;
void PeekMSG() {
    if (PeekMessage(&WndMessage, NULL, 0, 0, PM_REMOVE))
    {
        if (WndMessage.message == WM_QUIT) ExitProcess(0);
        else
        {
            TranslateMessage(&WndMessage);
            DispatchMessage(&WndMessage);
        }
    }
    if (mainkb.IsKeyPressed(VK_ESCAPE)) {
        ExitProcess(0);
    }
    if (mainkb.IsKeyPressed(0x41)) {
        camX -= 3;
    }
    if (mainkb.IsKeyPressed(0x44)) {
        camX += 3;
    }
    if (mainkb.IsKeyPressed(0x57)) {
        camY -= 3;
    }
    if (mainkb.IsKeyPressed(0x53)) {
        camY += 3;
    }
}


int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Window W(hInstance, nCmdShow);

    Point Points[] = {
        Point(175, 1370, Stalkers, (char*)&"Деревня Новичков\0"),
        Point(240, 1670, Army, (char*)&"Южный блокпост\0"),
        Point(600, 1200, Bandits, (char*)&"АТП <<Кооператив Локомотив>>\0"),
        Point(460, 240, Bandits, (char*)&"Северный Блокпост\0"),
        Point(430, 790, Stalkers, (char*)&"Свиноферма\0"),
        Point(415, 1070, Stalkers, (char*)&"Зерноочистительный комплекс\0"),
        Point(520, 970, Army, (char*)&"Железнодорожный мост\0"),
        Point(325, 1260, Stalkers, (char*)&"Укрытие у вагона\0"),
    };


    Image NewGame("menu\\ng.bmp", 0, 0);
    Image ExitGame("menu\\exit.bmp", 0, 0);

    while (1) {
        if (true) {
            PeekMSG();

            GetCursorPos(&mouse);
            W.SwapBuffers();
            W.ClearBufferNC();
        }

        W.SetImageToBufferNC(NewGame, 10 , 10);
        if (NewGame.IsClicked(10, 10)) break;
        W.SetImageToBufferNC(ExitGame, 10, 80);
        if (ExitGame.IsClicked(10, 80)) ExitProcess(0);
    }

    Image Kordon("maps\\kordon.bmp\0", 0, 0);
    while (1) {

        if (true) {
            PeekMSG();

            GetCursorPos(&mouse);
            W.SwapBuffers();
            W.ClearBufferNC();
        }

        W.SetImageToBufferNC(Kordon, 0 - camX, 0 - camY); // MAP

        for (int i = 0; i < 8; i++) {
            if (Points[i].IsClicked()) continue;
            if (Points[i].GetOwnerId() != -1)
                //W.SetImageToBufferNC(
                //    Groups[Points[i].GetOwnerId()].GetImg(),
                //    Points[i].GetX() - camX,
                //    Points[i].GetY() - camY
                //);
                Groups[Points[i].GetOwnerId()].GetImg().SetToScreen(
                    W.GetBufferNC(),
                    Points[i].GetX() - camX,
                    Points[i].GetY() - camY
                );
            Points[i].Shtorka(mouse, W.GetBufferNC());
        }
    }
}