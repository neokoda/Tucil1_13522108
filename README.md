# Tugas Kecil 1 Strategi Algoritma : Cyberpunk 2077 Breach Protocol Solver

## Daftar Isi

- [Tugas kecil 1 Strategi Algoritma](#tugas-kecil-1-strategi-algoritma)
  - [Daftar Isi](#daftar-isi)
  - [Identitas Pembuat](#identitas-pembuat)
  - [Deskripsi Singkat](#deksripsi-singkat)
  - [Requirement Program](#requirement-program)
  - [Cara Mengompilasi Program](#cara-mengompilasi-program)
  - [Cara Menjalankan Program](#cara-menjalankan-program)

## Identitas Pembuat
Nama      : Muhammad Neo Cicero Koda
Kelas/NIM : K02/13522108

## Deskripsi Singkat

Program ini dibuat dengan bahasa C++. Konsep program ini terinspirasi dari minigame Breach Protocol Cyberpunk 2077. Minigame tersebut merupakan simulasi peretasan jaringan local ICE (Intrusion Countermeasures Electronics). Dalam program ini, terdapat matriks yang berisi token alfanumerik, sekuens yang memberikan reward, dan buffer. Buffer akan diisi dengan token pada matriks dengan pola horizontal-vertikal. Tujuan utama dari program ini adalah menentukan langkah paling optimal sehingga buffer berisi sekuens-sekuens yang memiliki total reward maksimal. Hal tersebut dilakukan dengan pendekatan brute force.

## Requirement Program
Pastikan agar perangkat yang sedang dipakai memiliki g++ untuk mengompilasi source file. Petunjuk untuk mengunduh g++ dapat dilihat di laman [ini](https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/)

## Cara Mengompilasi Program
Untuk mengompilasi program, pindah ke src terlebih dahulu dengan mengetik perintah:
```
cd src
```
Lalu, pada *root directory*, masukkan perintah:
```
g++ solver.cpp -o ../bin/solver.exe
```

## Cara Menjalankan Program
1. Pada folder src, masukkan perintah:
```
../bin/solver.exe
```
2. Masukkan angka 1 jika ingin melakukan input dari file atau angka 2 jika ingin melakukan input melalui keyboard
3. Jika melakukan input dari file, masukkan path ke file yang mengandung konfigurasi matriks, sekuens, dan buffer.
4. Jika melakukan input dari keyboard, masukkan konfigurasi token, buffer, matriks, dan sekuens yang digunakan.
5. Setelah melakukan input, solusi untuk file tersebut akan ditampilkan. Ketik y untuk menyimpan solusi dalam file dan n untuk tidak menyimpan solusi.