#include "admin.cpp"

using namespace std;

struct Transaksi
{
    string kode;
    string pembeli;
    string barang;
    int hariAwal;
    int bulanAwal;
    int tahunAwal;
    int hariAkhir;
    int bulanAkhir;
    int tahunAkhir;
    int totalDurasi;
    double totalBayar;
};

void bersihkanLayar();
void jedaTampilan();

int hitungHari(int h, int b, int t)
{
    return h + (b * 30) + (t * 365);
}

void cetakNota(Transaksi t)
{
    bersihkanLayar();
    cout << "\n   -----------------------------------------------\n";
    cout << "   |             NOTA PEMESANAN KENDARAAN        |\n";
    cout << "   -----------------------------------------------\n";
    cout << "   ID Pesanan    : " << t.kode << endl;
    cout << "   User          : " << t.pembeli << endl;
    cout << "   Kendaraan     : " << t.barang << endl;
    cout << "   -----------------------------------------------\n";
    cout << "   Durasi        : " << t.totalDurasi << " Hari" << endl;
    cout << "   Total Tagihan : Rp " << t.totalBayar << endl;
    cout << "   -----------------------------------------------\n";
    cout << "\n   Lanjutkan ke pembayaran...\n";
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
    cout << "   |                PESAN KENDARAAN              |\n";
    cout << "   -----------------------------------------------\n";
    cout << "   Kendaraan : " << b.nama << endl;
    cout << "   -----------------------------------------------\n";

    cout << "   Tanggal Mulai                      : "
         << t.hariAwal << "-" << t.bulanAwal << "-" << t.tahunAwal << endl;

    cout << "   Input Tanggal Selesai (DD MM YYYY) : ";
    cin >> t.hariAkhir >> t.bulanAkhir >> t.tahunAkhir;

    cout << "   -----------------------------------------------\n";

    int totalAwal = hitungHari(t.hariAwal, t.bulanAwal, t.tahunAwal);
    int totalAkhir = hitungHari(t.hariAkhir, t.bulanAkhir, t.tahunAkhir);

    t.totalDurasi = totalAkhir - totalAwal;

  
    if (t.totalDurasi > 0)
    {
        t.totalBayar = t.totalDurasi * b.harga;

        cetakNota(t);
    }
    else
    {
        cout << "\n   [Error] Tanggal selesai tidak valid (harus setelah tanggal mulai)!" << endl;
        jedaTampilan();
    }
}

void pilihBarangUntukDipesan()
{
    int subPilih = 0;
    int key;

    do
    {
        bersihkanLayar();
        cout << "\n   -----------------------------------------------\n";
        cout << "   |             P E S A N  B A R A N G          |\n";
        cout << "   -----------------------------------------------\n";

        for (int i = 0; i < jumlahBarang; i++)
        {

            string penanda = (i == subPilih) ? "\033[36m>> " : "   ";
            cout << "   " << penanda << left << setw(15) << daftarBarang[i].nama
                 << "- Rp" << daftarBarang[i].harga << "\033[0m" << endl;
        }

        cout << "   -----------------------------------------------\n";

        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72) 
                subPilih = (subPilih == 0) ? jumlahBarang - 1 : subPilih - 1;
            else if (key == 80) 
                subPilih = (subPilih == jumlahBarang - 1) ? 0 : subPilih + 1;
        }
    } while (key != 13); 
    prosesPesanan(user[user_id].username, daftarBarang[subPilih]);
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

        string menu[] = {"Lihat Barang", "Pesan Barang", "Logout"};
        for (int i = 0; i < 3; i++)
        {
            cout << endl
                 << "              " << (i == subPilih ? "\033[36m>> " : "   ") << menu[i] << "\033[0m" << endl;
        }
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 3 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 3) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    switch (subPilih)
    {
    case 0:
        readBarang();
        dashboardUser();
        break;
    case 1:
        pilihBarangUntukDipesan();
        break;
    case 2:
        spasi();
        cout << " Apakah anda yakin ingin logout ? (y/n) ";
        cin >> yesorno;

        if (yesorno == 'y' || yesorno == 'Y')
        {
            spasi();
            cout << " Logout berhasil!" << endl;
            lanjutTampilan();
            menuUtama();
        }
        else
            dashboardAdmin();
        break;
    }
}