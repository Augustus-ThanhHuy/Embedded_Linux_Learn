#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>  // dùng isascii(), toupper(), islower()

// Hàm xử lý phía tiến trình cha (nhận dữ liệu từ người dùng, gửi cho con)
void user_handler(int input_pipe[], int output_pipe[]) {
    int c;   // ký tự nhập
    int rc;  // mã lỗi trả về

    // Đóng các đầu không cần thiết
    close(input_pipe[1]);   // cha không ghi vào pipe đọc
    close(output_pipe[0]);  // cha không đọc từ pipe ghi

    // Vòng lặp nhận dữ liệu từ người dùng và xử lý
    while ((c = getchar()) > 0) {
        // Ghi vào ống
        rc = write(output_pipe[1], &c, 1);
        if (rc == -1) {
            perror("user_handler: pipe write error");
            close(input_pipe[0]);
            close(output_pipe[1]);
            exit(1);
        }

        // Đọc từ ống pipe con trả về
        rc = read(input_pipe[0], &c, 1);
        if (rc <= 0) {
            perror("user_handler: read error");
            close(input_pipe[0]);
            close(output_pipe[1]);
            exit(1);
        }

        // In ra màn hình
        putchar(c);
    }

    // Đóng pipe khi xong
    close(input_pipe[0]);
    close(output_pipe[1]);
    exit(0);
}

// Hàm xử lý phía tiến trình con (biến đổi dữ liệu từ cha)
void translator(int input_pipe[], int output_pipe[]) {
    int c;
    int rc;

    // Đóng đầu không cần dùng
    close(input_pipe[1]);   // con không ghi vào pipe đọc
    close(output_pipe[0]);  // con không đọc từ pipe ghi

    // Đọc dữ liệu từ pipe cha gửi
    while (read(input_pipe[0], &c, 1) > 0) {
        // Chuyển thành chữ hoa nếu là ký tự thường
        if (isascii(c) && islower(c))
            c = toupper(c);

        // Ghi lại kết quả vào pipe gửi về cha
        rc = write(output_pipe[1], &c, 1);
        if (rc == -1) {
            perror("translator: write");
            close(input_pipe[0]);
            close(output_pipe[1]);
            exit(1);
        }
    }

    // Đóng pipe khi xong
    close(output_pipe[1]);
    exit(0);
}

// Chương trình chính
int main() {
    int user_to_translator[2];     // pipe từ cha tới con
    int translator_to_user[2];     // pipe từ con về cha
    int pid;
    int rc;

    // Tạo pipe thứ nhất
    rc = pipe(user_to_translator);
    if (rc == -1) {
        perror("main: pipe user_to_translator error");
        exit(1);
    }

    // Tạo pipe thứ hai
    rc = pipe(translator_to_user);
    if (rc == -1) {
        perror("main: pipe translator_to_user error");
        exit(1);
    }

    // Tạo tiến trình con
    pid = fork();
    switch (pid) {
        case -1:
            perror("main: fork error");
            exit(1);

        case 0:  // tiến trình con
            translator(user_to_translator, translator_to_user);
            break;

        default: // tiến trình cha
            user_handler(translator_to_user, user_to_translator);
    }

    return 0;
}
