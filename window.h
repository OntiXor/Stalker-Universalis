#pragma once
bool LeftButton = false;
HWND hWnd;
const int ISizeX = 50;
const int ISizeY = 50;
const int ISSizeX = 15;
const int ISSizeY = 15;

const int StdIcoSizeX = 50;
const int StdIcoSizeY = 50;

class Image {
public:
    Image(){}
    Image(string path, int sx, int sy) {
        this->path = path;
        if (path.find(".ico") != string::npos) ico = true;
        else ico = false;

        WndDC = GetWindowDC(hWnd);
        hgt, wdt = sx, sy;

        if (ico) {
            if (!sx) {
                wdt = StdIcoSizeX;
            }
            if (!sy) {
                hgt = StdIcoSizeY;
            }
            img = LoadImageA(
                NULL,
                (LPSTR)path.c_str(),
                IMAGE_ICON,
                0,
                0,
                LR_LOADFROMFILE
            ); if (img != NULL) cout << "An icon was loaded: " << path << endl;
            else {
                cout << "Error! Cannot Load a file: " << path;
                printf(". Error 0x%X\n", GetLastError());
            }
        }
        else {
            BITMAP* bmp = new BITMAP;
            img = LoadImageA(
                NULL,
                (LPSTR)path.c_str(),
                IMAGE_BITMAP,
                0,
                0,
                LR_LOADFROMFILE
            ); 

            if (img != NULL) cout << "Image was loaded: " << path << endl;
            else cout << "Error! Cannot Load a file: " << path << ". Error " << GetLastError() << endl;

            iDC = CreateCompatibleDC(WndDC);
            SelectObject(iDC, img);
            ReleaseDC(hWnd, iDC);
            GetObjectA(img, sizeof(BITMAP), bmp);
            if (sy == 0)
                hgt = bmp->bmHeight;
            else
                hgt = sy;
            if (sx == 0)
                wdt = bmp->bmWidth;
            else
                wdt = sx;
            delete bmp;
        }        
    }
    Image(string path) {
        *this = Image(path, 0, 0);
    }
    bool IsClicked(int x, int y) {
        if (LeftButton) {
            if (ico) {
                if (mouse.x >= x - camX &&
                    mouse.y >= y - camY &&
                    mouse.x <= x - camX + wdt &&
                    mouse.y <= y - camY + hgt
                    ) return true;
            }
            else
            {
                if (mouse.x >= x - camX &&
                    mouse.y >= y - camY &&
                    mouse.x <= x - camX + wdt &&
                    mouse.y <= y - camY + hgt
                    ) return true;
            }
        }
        return false;
    }
    bool SetToScreen(HDC screen, int x, int y) {
        if (!ico) BitBlt(screen, x, y, wdt, hgt, iDC, NULL, NULL, SRCCOPY);
        else DrawIconEx(screen, x, y, (HICON)img, wdt, hgt, NULL, NULL, DI_NORMAL);
        if (GetLastError()) {
            cout << "Image was not set into screen. Code: ";
            printf("0x%X\n", GetLastError());
            return false;
        }
        return true;
    }
    HDC GetDC() {
        return iDC;
    }
    int GetWidth() {
        return wdt;
    }
    int GetHeight() {
        return hgt;
    }

    int x, y;

private:
    int hgt, wdt;
    HANDLE img;
    bool ico;
    HDC WndDC, iDC;
    string path;
};

LRESULT __stdcall WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        ExitProcess(0);
        break;
    case WM_LBUTTONDOWN:
        LeftButton = true;
        break;

    default:
        LeftButton = false;
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

class Window {
public:
    struct {
        int x, y;
    } resolution;
private:
    WNDCLASSEX wcex;
    HDC WndDC;
    HINSTANCE hInstance;
    int nCmdShow;
    Image* buffers;
    Image BGround;

    void InitBuffers() {
        buffers = new Image[2];

        BGround = Image((char*)&"background.bmp\0", 1920, 1080);
        buffers[0] = Image((char*)&"background.bmp\0", 1920, 1080);
        buffers[1] = Image((char*)&"background.bmp\0", 1920, 1080);
    };

public:
    Window(HINSTANCE hInstance, int nCmdShow) {
        this->hInstance = hInstance;
        this->nCmdShow = nCmdShow;

        HDC hDCScreen = GetDC(NULL);
        resolution.x = GetDeviceCaps(hDCScreen, HORZRES);
        resolution.y = GetDeviceCaps(hDCScreen, VERTRES);
        ReleaseDC(NULL, hDCScreen);

        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_OWNDC;
        wcex.lpfnWndProc = WindowProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = L"OntixorWndClass";
        wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        RegisterClassEx(&wcex);
        hWnd = CreateWindowEx(0,
            L"OntixorWndClass",
            L"Ontixor Engine",
            WS_POPUP | WS_VISIBLE,
            0,
            0,
            resolution.x,
            resolution.y,
            NULL,
            NULL,
            hInstance,
            NULL);

        ShowWindow(hWnd, nCmdShow);
        WndDC = GetWindowDC(hWnd);
        InitBuffers();
    }
    void SwapBuffers() {
        Image gap = buffers[0];
        buffers[0] = buffers[1];
        buffers[1] = gap;
        buffers[0].SetToScreen(WndDC, 0, 0);
    }
    void SetImageToBufferNC(Image img, int x, int y) {
        img.SetToScreen(buffers[1].GetDC(), x, y);
    }
    void ClearBufferNC() {
        BGround.SetToScreen(buffers[1].GetDC(), 0, 0);
    }
    HDC GetBufferNC() {
        return buffers[1].GetDC();
    }
};