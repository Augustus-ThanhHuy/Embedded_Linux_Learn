#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* Cài đặt hàm dùng thực thi tiến trình con */
void do_child(int data_pipe[2]) {
    int c;   /* Chứa dữ liệu đọc từ tiến trình cha */
    int rc;  /* Lưu trạng thái trả về của read() */

    // Đóng đầu ghi pipe vì tiến trình con không cần
    close(data_pipe[1]);

    // Đọc dữ liệu từ đầu đọc pipe và in ra màn hình
    while ((rc = read(data_pipe[0], &c, 1)) > 0) {
        putchar(c);
    }

    // Khi không còn dữ liệu, thoát tiến trình con
    exit(0);
}

/* Cài đặt hàm xử lý công việc của tiến trình cha */
void do_parent(int data_pipe[2]) {
    int c;   /* Dữ liệu đọc được do người dùng nhập vào */
    int rc;  /* Lưu trị trả về của getchar() */

    // Đóng đầu đọc pipe vì tiến trình cha không cần
    close(data_pipe[0]);

    // Đọc dữ liệu từ bàn phím và ghi vào pipe
    while ((c = getchar()) > 0) {
        rc = write(data_pipe[1], &c, 1);
        if (rc == -1) {
            perror("Parent: pipe write error");
            close(data_pipe[1]);
            exit(1);
        }
    }

    // Đóng đầu ghi pipe để báo kết thúc dữ liệu
    close(data_pipe[1]);
    exit(0);
}

/* Chương trình chính */
int main() {
    int data_pipe[2]; /* Mảng chứa số mô tả đọc ghi của pipe */
    int pid;          /* pid của tiến trình con */
    int rc;           /* Lưu mã lỗi trả về */

    // Tạo đường ống
    rc = pipe(data_pipe);
    if (rc == -1) {
        perror("pipe create error");
        exit(1);
    }

    // Tạo tiến trình con
    pid = fork();
    switch (pid) {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            do_child(data_pipe);  // Tiến trình con
            break;
        default:
            do_parent(data_pipe); // Tiến trình cha
            break;
    }

    return 0;
}
