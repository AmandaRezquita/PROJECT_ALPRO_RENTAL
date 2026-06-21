#include "admin.cpp"
using namespace std;

int jumlahRiwayat = 0;
Transaksi riwayatTransaksi[100];
int subPilih_t = 0;
void bersihkanLayar();
void jedaTampilan();

int hitungHari(int h, int b, int t)
{
    return h + (b * 30) + (t * 365);
}

void prosesPembayaran(Transaksi t)
{
    double uangDibayar, kembalian;
    bool pembayaranBerhasil = false;

    bersihkanLayar();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |              P E M B A Y A R A N            |\n";
    cout << "   -----------------------------------------------\n";
    cout << "   Total Tagihan : Rp " << t.totalBayar << endl;
    cout << "   -----------------------------------------------\n";

    do
    {
        cout << "   Masukkan jumlah uang pembayaran : Rp ";
        cin >> uangDibayar;

        if (uangDibayar >= t.totalBayar)
        {
            kembalian = uangDibayar - t.totalBayar;
            pembayaranBerhasil = true;
        }
        else
        {
            cout << "   [Error] Uang tidak cukup! Kekurangan: Rp "
                 << (t.totalBayar - uangDibayar) << endl;
            cout << "   Silakan masukkan jumlah yang benar.\n"
                 << endl;
        }
    } while (!pembayaranBerhasil);

    cout << "   -----------------------------------------------\n";
    cout << "   Status        : Pembayaran Berhasil!" << endl;
    cout << "   Kembalian     : Rp " << kembalian << endl;
    cout << "   -----------------------------------------------\n";
    riwayatTransaksi[jumlahRiwayat].kode = t.kode;
    riwayatTransaksi[jumlahRiwayat].pembeli = t.pembeli;
    riwayatTransaksi[jumlahRiwayat].barang = t.barang;
    riwayatTransaksi[jumlahRiwayat].totalBayar = t.totalBayar;
    riwayatTransaksi[jumlahRiwayat].dikembalikan = false;

    jumlahRiwayat++;
    daftarBarang[subPilih_t].available = false;
    cout << "\n   [OK] Transaksi berhasil disimpan ke riwayat!" << endl;
    lanjutTampilan();
    dashboardUser();
}

void cetakNota(Transaksi t)
{
    bersihkanLayar();
    cout << "   -----------------------------------------------\n";
    cout << "   |             N O T A  P E S A N A N          |\n";
    cout << "   -----------------------------------------------\n";
    cout << "   ID Pesanan    : " << t.kode << endl;
    cout << "   User          : " << t.pembeli << endl;
    cout << "   Kendaraan     : " << t.barang << endl;
    cout << "   -----------------------------------------------\n";
    cout << "   Durasi        : " << t.totalDurasi << " Hari" << endl;
    cout << "   Total Tagihan : Rp " << t.totalBayar << endl;
    cout << "   -----------------------------------------------\n";
    cout << "\n   Silahkan lanjutkan ke pembayaran\n";

    lanjutTampilan();
}

void prosesPesanan(string namaUser, Barang b)
{
    Transaksi t;
    t.pembeli = namaUser;
    t.barang = b.nama;
    t.kode = "TRX-" + namaUser.substr(0, 2);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    t.hariAwal = ltm->tm_mday;
    t.bulanAwal = 1 + ltm->tm_mon;
    t.tahunAwal = 1900 + ltm->tm_year;

    bersihkanLayar();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |          S E W A  K E N D A R A A N         |\n";
    cout << "   -----------------------------------------------\n";
    cout << "      Nama       : " << b.nama << endl;
    cout << "\n      Harga      : Rp" << b.harga << endl;
    cout << "\n      Deskripsi  : " << b.deskripsi << endl;
    cout << "\n      " << BLUE << "\033]8;;" << b.url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
    cout << "   ===============================================\n";
    cout << "   Tanggal Mulai                      : "
         << t.hariAwal << "-" << t.bulanAwal << "-" << t.tahunAwal << endl;

    bool tanggalValid = false;
    do
    {
        cout << "   Input Tanggal Selesai (DD MM YYYY) : ";
        cin >> t.hariAkhir >> t.bulanAkhir >> t.tahunAkhir;

        int totalAwal = hitungHari(t.hariAwal, t.bulanAwal, t.tahunAwal);
        int totalAkhir = hitungHari(t.hariAkhir, t.bulanAkhir, t.tahunAkhir);

        int selisih = totalAkhir - totalAwal;

        if (selisih == 0)
        {
            t.totalDurasi = 1;
        }
        else
        {
            t.totalDurasi = selisih;
        }

        if (t.totalDurasi >= 1)
        {
            tanggalValid = true;
        }
        else
        {
            cout << "   [Error] Tanggal tidak valid! Tanggal selesai tidak boleh sebelum tanggal mulai.\n"
                 << endl;
        }
    } while (!tanggalValid);

    cout << "   -----------------------------------------------\n";
    t.totalBayar = t.totalDurasi * b.harga;
    tampilkanLoading();
    cetakNota(t);
    prosesPembayaran(t);
}

void pilihBarangUntukDipesan()
{
    int key;

    do
    {
        bersihkanLayar();
        cout << "\n   -----------------------------------------------\n";
        cout << "   |             S E W A  B A R A N G            |\n";
        cout << "   -----------------------------------------------\n";
        for (int i = 0; i < jumlahBarang; i++)
        {
            string penanda = (i == subPilih_t) ? "\033[36m>> " : "   ";
            cout << "              " << penanda << left << setw(10) << daftarBarang[i].nama
                 << "- Rp" << daftarBarang[i].harga << "\033[0m" << endl;
        }

        cout << "   ===============================================\n";

        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih_t = (subPilih_t == 0) ? jumlahBarang - 1 : subPilih_t - 1;
            else if (key == 80)
                subPilih_t = (subPilih_t == jumlahBarang - 1) ? 0 : subPilih_t + 1;
        }
    } while (key != 13);
    prosesPesanan(userList[user_id].akun.username, daftarBarang[subPilih_t]);
}

void lihatHistory()
{
    bersihkanLayar();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |            R I W A Y A T  S E W A           |\n";
    cout << "   -----------------------------------------------\n";

    bool ada = false;
    for (int i = 0; i < jumlahRiwayat; i++)
    {
        if (riwayatTransaksi[i].pembeli == userList[user_id].akun.username)
        {
            cout << "   ID         : " << riwayatTransaksi[i].kode << endl;
            cout << "   Kendaraan  : " << riwayatTransaksi[i].barang << endl;

            cout << "   Status     : ";
            if (!riwayatTransaksi[i].dikembalikan)
            {
                cout << "\033[31m[BELUM DIKEMBALIKAN]\033[0m" << endl;
            }
            else
            {
                cout << "\033[32m[SUDAH DIKEMBALIKAN]\033[0m" << endl;
            }

            cout << "   -----------------------------------------------\n";
            ada = true;
        }
    }

    if (!ada)
        cout << "   Belum ada riwayat transaksi.\n";
    lanjutTampilan();
}

void menuProfil()
{
    bersihkanLayar();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |             P R O F I L  U S E R            |\n";
    cout << "   -----------------------------------------------\n";
    cout << "   Username     : " << userList[user_id].akun.username << endl;
    cout << "   -----------------------------------------------\n";

    clearBuffer();
    cout << "   Nama Lengkap : ";
    getline(cin, userList[user_id].data.namaLengkap);
    cout << "   No. Telepon  : ";
    getline(cin, userList[user_id].data.noTelp);
    cout << "   Alamat       : ";
    getline(cin, userList[user_id].data.alamat);

    userList[user_id].data.profilLengkap = true;
    cout << "\n   [OK] Profil berhasil disimpan!\n";
    lanjutTampilan();
}

void ajukanPengembalian()
{
    bersihkanLayar();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |     A J U K A N  P E N G E M B A L I A N    |\n";
    cout << "   -----------------------------------------------\n";

    int indexDitemukan[100];
    int count = 0;

    for (int i = 0; i < jumlahRiwayat; i++)
    {
        if (riwayatTransaksi[i].pembeli == userList[user_id].akun.username &&
            !riwayatTransaksi[i].dikembalikan && !riwayatTransaksi[i].diajukan)
        {

            cout << "   " << count + 1 << ". " << riwayatTransaksi[i].barang
                 << " (ID: " << riwayatTransaksi[i].kode << ")" << endl;
            indexDitemukan[count] = i;
            count++;
        }
    }

    if (count == 0)
    {
        cout << "\n   Tidak ada kendaraan yang perlu dikembalikan.\n";
    }
    else
    {
        int pilih;
        cout << "\n   Pilih nomor kendaraan yang ingin dikembalikan: ";
        cin >> pilih;

        if (pilih > 0 && pilih <= count)
        {
            int targetIdx = indexDitemukan[pilih - 1];
            riwayatTransaksi[targetIdx].diajukan = true;

            cout << "\n   [OK] Pengajuan berhasil dikirim!\n";
            cout << "   Mohon tunggu admin memproses verifikasi Anda.\n";
        }
    }
    lanjutTampilan();
}
void dashboardUser()
{
    int subPilih = 0;
    int key;
    do
    {
        bersihkanLayar();
        cout << "\n";
        cout << "   ===============================================\n";
        cout << "   |                                             |\n";
        cout << "   |          D A S H B O A R D  U S E R         |\n";
        cout << "   |                                             |\n";
        cout << "   ===============================================\n";
        cout << "   \033[36m[Selamat datang : " << userList[user_id].akun.username << "]\033[0m\n";
        cout << "   -----------------------------------------------\n";
        cout << "                                      " << "\033[36m[" << tanggal_sekarang << "]\033[0m\n";

        string menu[] = {"Lihat Barang", "Sewa Barang", "Profil Saya", "Riwayat Sewa", "Ajukan Pengembalian", "Logout"};
        for (int i = 0; i < 6; i++)
        {
            cout << endl
                 << "              " << (i == subPilih ? "\033[36m>> " : "   ") << menu[i] << "\033[0m" << endl;
        }
        cout << "\n   ===============================================\n";
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 5 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 5) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    switch (subPilih)
    {
    case 0:
        readBarang();
        dashboardUser();
        break;
    case 1:
        if (!userList[user_id].data.profilLengkap)
        {
            cout << "\n   \033[31m[!] PERINGATAN: Profil belum lengkap!\033[0m\n";
            cout << "   Harap isi profil melalui menu 'Profil Saya' sebelum menyewa.\n";
            lanjutTampilan();
            dashboardUser();
        }
        else
        {
            pilihBarangUntukDipesan();
        }
        break;
    case 2:
        menuProfil();
        dashboardUser();
        break;
    case 3:
        lihatHistory();
        dashboardUser();
        break;
    case 4:
        ajukanPengembalian();
        dashboardUser();
        break;
    case 5:
        cout << "   Apakah anda yakin ingin logout ? (y/n) ";
        cin >> yesorno;

        if (yesorno == 'y' || yesorno == 'Y')
        {
            cout << "\n   [Logout berhasil!]" << endl;
            lanjutTampilan();
            menuUtama();
        }
        else
            dashboardUser();
    }
}