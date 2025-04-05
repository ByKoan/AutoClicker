// gcc main.c -o AutoClicker.exe 

#include <windows.h>
#include <stdio.h>

void clickMouse() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    
    // Presiona el botón izquierdo
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    
    Sleep(100); // Tiempo entre presionar y soltar (ajustable)
    
    // Suelta el botón izquierdo (Comenta las dos siguientes lineas si quieres que se quede presionado el click)
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    int running = 0;  // Variable para controlar el estado del autoclicker (0 = detenido, 1 = activo)
    
    printf("Presione F6 para iniciar y F7 para detener el autoclicker.\n");
    
    while (1) {
        // Inicia el autoclicker si se presiona F6 y no está en ejecución
        if (GetAsyncKeyState(VK_F6) & 0x8000) { //VK_F6 es la tecla F6
            if (!running) {
                running = 1;
                printf("Autoclicker iniciado.\n");
                Sleep(1); // Retardo para evitar múltiples detecciones (debounce)
            }
        }
        
        // Detiene el autoclicker si se presiona F7 y está en ejecución
        if (GetAsyncKeyState(VK_F7) & 0x8000) { //VK_F6 es la tecla F7
            if (running) {
                running = 0;
                printf("Autoclicker detenido.\n");
                Sleep(1); // Retardo para evitar múltiples detecciones (debounce)
            }
        }
        
        // Si está activo, ejecuta el clic del mouse
        if (running) {
            clickMouse();
        }
        
        Sleep(10); // Pequeña espera para no saturar la CPU
    }
    
    return 0;
}
