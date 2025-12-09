## **Informasi Tantangan**

* **Kategori:** Reverse Engineering  
* **Tingkat Kesulitan:** Mudah (Easy)  
* **File:** challenge (Linux/Mac) atau challenge.exe (Windows)

## **Analisis**

1. **Analisis Statis:**  
   * Binary tidak di-*stripped* (symbol masih ada), memudahkan analisis.  
   * Terdapat string palsu (decoy) pada variabel decoys\[\] seperti `FLAG{fake\_flag\_123}` untuk mengecoh penggunaan strings.  
2. **Flow Program:**  
   * `main()` memanggil `check\_debugger()`. Jika debugger terdeteksi (berdasarkan selisih waktu eksekusi `clock()`), program keluar.  
   * Program meminta input pengguna dan membandingkannya menggunakan `verify\_input()`.  
3. **Logika Flag:**  
   * Flag tidak disimpan dalam *plain text*.  
   * Fungsi `assemble\_flag()` menyusun flag dari 4 array byte (`enc1`, `enc2`, `enc3`, `enc4`).  
   * Setiap byte di-dekripsi menggunakan operasi **XOR** dengan kunci 0x42.

## **Langkah Penyelesaian**

1. Buka binary menggunakan disassembler (Ghidra/IDA/Binary Ninja).  
2. Temukan fungsi `assemble\_flag` atau logika di mana enc array dimuat.  
3. Identifikasi nilai Hex dari array global:  
   * `enc1`: `04 0E 03 05 39`
   * `enc2`: `23 30 23 1D 23 30 23 1D`
   * `enc3`: `7C 6D 6D 7E`
   * `enc4`: `3F`
4. Lakukan operasi XOR `0x42` pada setiap byte tersebut.

## **Flag**

`FLAG{ara\_ara\_\>//\<}`