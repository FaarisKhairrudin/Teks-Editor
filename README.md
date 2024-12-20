# Editor Teks Sederhana dengan Linked List dan Stack

## Deskripsi Proyek
Proyek ini adalah sebuah _Text Editor_ sederhana yang dirancang untuk mereplikasi fitur utama dari editor teks modern. Hal yang unik dari implementasi ini adalah penggunaan **_Linked List_** untuk menyimpan karakter dan **_Stack_** untuk mengimplementasikan fungsi **undo** dan **redo**. Tujuan utama dari proyek ini adalah untuk mendalami pemahaman tentang struktur data seperti linked list, stack, dan pointer dengan mengintegrasikannya ke dalam aplikasi praktis.

### Fitur Utama
- **Input dan Penghapusan Teks:** Menambahkan dan menghapus teks secara langsung melalui input keyboard.
- **Navigasi Kursor:** Memindahkan kursor secara bebas ke atas, bawah, kiri, dan kanan.
- **Blok dan Manipulasi Teks:** Memblokir (memilih) teks untuk dihapus, ditambahkan, atau melakukan operasi copy-paste.
- **Copy dan Paste:** Melakukan operasi salin-tempel seperti editor teks standar.
- **Cari dan Ganti:** Menemukan teks tertentu dan menggantinya dengan konten baru.
- **Undo dan Redo:** Membatalkan atau mengulangi perubahan menggunakan implementasi berbasis stack.

## Penjelasan File
- **main.cpp:** Program utama untuk menjalankan editor teks.
- **header.h:** Berisi ADT (Abstract Data Type) dari program ini.
- **basic.cpp:** Berisi fungsi-fungsi primitif untuk struktur data, seperti `insertFirst`, `insertLast`, `deleteFirst`, `createList`, `createElm`, dan lainnya.
- **textOperator.cpp:** Berisi fungsi utama untuk menjalankan fitur-fitur editor teks, seperti penambahan teks, penghapusan teks, Undo, Redo dan lainnya.
- **cursorOperator.cpp:** Berisi fungsi untuk fitur yang berkaitan dengan kursor, seperti navigasi kursor dan pemblokiran teks.
- **display.cpp:** Berisi fungsi untuk tampilan visual agar editor teks terlihat lebih menarik.


---
### 
**kelompok: Penyu Ngambek**
1. Faaris Khairrudin  (103052300115)
2. Muhammad Umar      (103052330101)
