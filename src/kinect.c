#include <stdio.h>
#include <stdlib.h>
#include <libfreenect.h>

freenect_context *f_ctx;
freenect_device *f_dev;
int user_device_number = 0; // Normalmente 0 se você tiver apenas um Kinect

void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp) {
    // Callback para dados de profundidade - não usado neste exemplo
}

void rgb_cb(freenect_device *dev, void *rgb, uint32_t timestamp) {
    // Salva uma imagem RGB capturada pelo Kinect
    FILE *image = fopen("output_image.ppm", "wb");
    if (image == NULL) {
        printf("Erro ao abrir o arquivo para escrita\n");
        return;
    }
    fprintf(image, "P6\n# Kinect RGB test\n640 480\n255\n");
    fwrite(rgb, 640*480*3, 1, image);
    fclose(image);
    printf("Imagem salva como output_image.ppm\n");

    // Depois de salvar a imagem, podemos sair do loop principal
    freenect_stop_video(dev);
    freenect_close_device(dev);
    freenect_shutdown(f_ctx);
    exit(0);
}

int main() {
    if (freenect_init(&f_ctx, NULL) < 0) {
        printf("freenect_init() falhou\n");
        return 1;
    }

    if (freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
        printf("Não foi possível abrir o dispositivo\n");
        freenect_shutdown(f_ctx);
        return 1;
    }

    freenect_set_depth_callback(f_dev, depth_cb);
    freenect_set_video_callback(f_dev, rgb_cb);
    freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB));

    freenect_start_video(f_dev);

    while (freenect_process_events(f_ctx) >= 0) {
        // Processa eventos do Kinect até que a captura de imagem seja concluída
    }

    return 0;
}

