#include <iostream>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <limits>
using namespace std;

#define BLUE "\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

const int MAX = 100;
int user_id = -1;
int jumlahUser = 2;
int pilihMenu = 0;
int jumlahBarang = 0;
int edit;
int jumlahRiwayat = 0;
int subPilih_t = 0;
char yesorno;

void dashboardAdmin();
void dashboardUser();
void kelolaBarang();
void createBarang();
void readBarang(bool isAdmin);
void pilih_Barang_Edit();
void deleteBarang();
void bersihkanLayar();
void jedaTampilan();

string getValidatedInput(string prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << RED << "   [!] Input tidak boleh kosong!" << RESET << endl;
        }
    } while (input.empty());
    return input;
}

string getTanggalSekarang()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int d = ltm->tm_mday;
    int m = 1 + ltm->tm_mon;
    int y = 1900 + ltm->tm_year;

    string hari = (d < 10 ? "0" : "") + to_string(d);
    string bulan = (m < 10 ? "0" : "") + to_string(m);
    string tahun = to_string(y);

    return hari + "-" + bulan + "-" + tahun;
}

string tanggal_sekarang = getTanggalSekarang();

struct Account
{
    string username;
    string password;
};

struct Profil
{
    string namaLengkap;
    string noTelp;
    string alamat;
    bool profilLengkap = false;
};

struct User
{
    Account akun;
    Profil data;
};

struct Barang
{
    string url;
    string nama;
    int harga;
    string deskripsi;
    bool available;
};

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
    bool dikembalikan = false;
    bool diajukan = false;
};

Account admin[1];
Barang daftarBarang[MAX];
User userList[MAX];
Transaksi riwayatTransaksi[MAX];
string tempJenis, tempMerk, tempDeskripsi;

void printGoRentSmall()
{
    cout << CYAN;
    cout << "       ___     ___         _               " << endl;
    cout << "      / __|___| _ \\___ _ _| |_             " << endl;
    cout << "     | (_ / _ \\   / -_) ' \\  _|  _   _   _ " << endl;
    cout << "      \\___\\___/_|_\\___|_||_\\__| (_) (_) (_)" << endl;
    cout << RESET << endl;
}

void printGoRent()
{
    cout << CYAN << R"(
  /$$$$$$   /$$$$$$  /$$$$$$$                        /$$    
 /$$__  $$ /$$__  $$| $$__  $$                      | $$    
| $$  \__/| $$  \ $$| $$  \ $$  /$$$$$$  /$$$$$$$  /$$$$$$ 
| $$ /$$$$| $$  | $$| $$$$$$$/ /$$__  $$| $$__  $$|_  $$_/ 
| $$|_  $$| $$  | $$| $$__  $$| $$$$$$$$| $$  \ $$  | $$   
| $$  \ $$| $$  | $$| $$  \ $$| $$_____/| $$  | $$  | $$ /$$
|  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$$| $$  | $$  |  $$$$/ 
 \______/  \______/ |__/  |__/ \_______/|__/  |__/   \___/  
    )" << RESET
         << endl;
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void spasi()
{
    cout << endl
         << '\t' << "     ";
}

void bersihkanLayar()
{
    cout << "\033[2J\033[H";
    system("cls");
}

void jedaTampilan()
{
    cout << "\n>> Tekan ENTER untuk kembali...";
    _getch();
}

void lanjutTampilan()
{
    cout << "\n>> Tekan ENTER untuk lanjut...";
    _getch();
}

void tampilkanLoading()
{
    string frame = "/-\\|";
    for (int i = 0; i < 20; i++)
    {
        cout << "\r   [ " << frame[i % 4] << " ] Sedang memproses nota...";
        for (long long j = 0; j < 1000000000; j++)
            ;
    }
    cout << "\r   [ OK ] Nota berhasil diproses!             " << endl;
    for (long long j = 0; j < 2000000000; j++)
        ;
}

void inisialisasiDummyData()
{
    if (jumlahBarang == 0)
    {
        daftarBarang[0] = {
            "https://kenh14cdn.com/203336854389633024/2022/11/28/photo-17-1669604198602829180940.jpg",
            "Vario",
            150000,
            "Jenis     : Motor\n"
            "                   Merk      : Honda\n"
            "                   Catatan   : Tes",
            true};

        daftarBarang[1] = {
            "https://www.honda.ca/-/media/Brands/Honda/Models/CR-V/2026/04-Trims/BAP/EX-L/SRSM/MY26_CR-V_EXL_AWD_SRSM_3250x2400_Desktop_BAPColourSelector_01.png",
            "CRV",
            250000,
            "Jenis     : Mobil\n"
            "                   Merk      : Honda\n"
            "                   Catatan   : Tes",
            true};
        jumlahBarang = 2;
    }
}

void dataAwal()
{
    admin[0].username = "admin";
    admin[0].password = "admin123";
    userList[0].akun.username = "user1";
    userList[0].akun.password = "123";
    userList[0].data.profilLengkap = false;

    userList[1].akun.username = "user2";
    userList[1].akun.password = "456";
    userList[1].data.profilLengkap = false;
}

void tampilkanVespa()
{
    cout << "\t                                        ,-~ |" << endl;
    cout << "\t     ________________                o==]___|" << endl;
    cout << "\t    |                |                \\ \\" << endl;
    cout << "\t    |________________|                /\\ \\" << endl;
    cout << "\t__  /  _,-----._     )             |  \\ \\." << endl;
    cout << "\t|_||/_-~         `.   /()          |  /|]_|_____" << endl;
    cout << "\t  |//             \\ |              \\/ /_-~     ~-_" << endl;
    cout << "\t  //________________||              / //__________\\" << endl;
    cout << "\t //__|______________| \\____________/ //___/-\\ \\~-_" << endl;
    cout << "\t((_________________/_-o___________/_//___/  /\\,\\  \\" << endl;
    cout << "\t |__/(  ((====)o===--~~                 (  ( (o/)  )" << endl;
    cout << "\t      \\  ``==' /                         \\  `--'  /" << endl;
    cout << "\t       `-.__,-'                           `-.__,-'" << endl;
}

bool cekAdmin(string u, string p)
{
    return (u == admin[0].username && p == admin[0].password);
}

bool cekUser(string u, string p)
{
    for (int i = 0; i < jumlahUser; i++)
    {
        if (u == userList[i].akun.username && p == userList[i].akun.password)
        {
            user_id = i;
            return true;
        }
    }
    return false;
}

bool cekUsername(string u)
{
    if (u == admin[0].username)
        return true;
    for (int i = 0; i < jumlahUser; i++)
    {
        if (u == userList[i].akun.username)
            return true;
    }
    return false;
}

void loginAdmin()
{
    bersihkanLayar();
    string u, p;
    cout << endl;
    printGoRentSmall();
    tampilkanVespa();
    cout << '\n';
    cout << "     ===========================================================\n";
    cout << endl;
    cout << "       ";
    cout << "      L O G I N  S E B E G A I  A D M I N\n";
    cout << endl;
    cout << '\t' << "     ";
    cout << "Username : ";
    cin >> u;
    cout << endl;
    cout << '\t' << "     ";
    cout << "Password : ";
    cin >> p;
    if (cekAdmin(u, p))
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << GREEN << "[Login Berhasil!]\n"
             << RESET
             << endl;
        lanjutTampilan();
        dashboardAdmin();
    }
    else
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << RED << "[Login Gagal!]\n"
             << RESET
             << endl;
        jedaTampilan();
    }
}

void loginUser()
{
    bersihkanLayar();
    string u, p;
    cout << endl;
    printGoRentSmall();
    tampilkanVespa();
    cout << '\n';
    cout << "     ===========================================================\n";
    cout << endl;
    cout << "       ";
    cout << "      L O G I N  S E B E G A I  U S E R\n";
    cout << endl;
    cout << '\t' << "     ";
    cout << "Username : ";
    cin >> u;
    cout << endl;
    cout << '\t' << "     ";
    cout << "Password : ";
    cin >> p;
    if (cekUser(u, p))
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << GREEN << "[Login Berhasil!]\n"
             << RESET << endl;
        lanjutTampilan();
        dashboardUser();
    }
    else
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << RED << "[Login Gagal!]\n"
             << RESET
             << endl;
    }
    jedaTampilan();
}

void registrasi()
{
    bersihkanLayar();
    string u, p, c;
    cout << endl;
    printGoRentSmall();
    tampilkanVespa();
    cout << '\n';
    cout << "     ===========================================================\n";
    cout << endl;
    cout << "       ";
    cout << "      R E G I S T R A S I\n";
    cout << endl;
    cout << '\t' << "     ";
    cout << "Username : ";
    cin >> u;
    if (cekUsername(u))
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << RED << "[Username sudah terdaftar!]" << RESET << endl;
    }
    else
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << "Password : ";
        cin >> p;
        cout << endl;
        cout << '\t' << "     ";
        cout << "Konfirmasi : ";
        cin >> c;
        if (p == c)
        {
            userList[jumlahUser].akun.username = u;
            userList[jumlahUser].akun.password = p;
            jumlahUser++;
            cout << endl;
            cout << '\t' << "     ";
            cout << GREEN << "[Akun berhasil dibuat!]\n"
                 << RESET;
        }
        else
        {
            cout << endl;
            cout << '\t' << "     ";
            cout << RED << "[Password tidak cocok!]\n"
                 << RESET;
        }
    }
    jedaTampilan();
}

void loginSubMenu()
{
    int key;
    int subPilih = 0;
    do
    {
        bersihkanLayar();
        cout << endl;
        printGoRentSmall();
        tampilkanVespa();
        cout << '\n';
        cout << "     ===========================================================\n";
        cout << endl;
        cout << "       ";
        cout << "      L O G I N\n";
        string menu[] = {"Login Sebagai Admin", "Login Sebagai User", "Kembali"};
        for (int i = 0; i < 3; i++)
        {
            cout << endl;
            cout << '\t' << "     ";
            if (i == subPilih)
                cout << BLUE << ">> " << menu[i] << RESET << endl;
            else
                cout << "   " << menu[i] << endl;
        }
        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                subPilih = (subPilih == 0) ? 2 : subPilih - 1;
            else if (key == 80)
                subPilih = (subPilih == 2) ? 0 : subPilih + 1;
        }
    } while (key != 13);

    if (subPilih == 0)
        loginAdmin();
    else if (subPilih == 1)
        loginUser();
}

void menuUtama()
{
    int key;
    do
    {
        bersihkanLayar();
        cout << endl;
        printGoRentSmall();
        tampilkanVespa();
        cout << '\n';
        cout << "     ==========================================================\n";
        cout << endl;
        cout << "     ";
        cout << "        S I S T E M  R E N T A L  K E N D A R A A N      \n";
        string menu[] = {"Login", "Registrasi", "Keluar"};
        for (int i = 0; i < 3; i++)
        {
            cout << endl;
            cout << '\t' << "     ";

            if (i == pilihMenu)
                cout << BLUE << ">> " << menu[i] << RESET << endl;
            else
                cout << "   " << menu[i] << endl;
        }

        key = _getch();
        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                pilihMenu = (pilihMenu == 0) ? 2 : pilihMenu - 1;
            else if (key == 80)
                pilihMenu = (pilihMenu == 2) ? 0 : pilihMenu + 1;
        }
    } while (key != 13);

    switch (pilihMenu)
    {
    case 0:
        loginSubMenu();
        menuUtama();
        break;
    case 1:
        registrasi();
        menuUtama();
        break;
    case 2:
        cout << "\nTerima Kasih!\n";
        break;
    }
}

void cetakHeaderFilter(string jenis, string merk)
{
    bersihkanLayar();
    cout << "\n";
    cout << "   -----------------------------------------------\n";
    cout << "   |           F I L T E R  B A R A N G          |\n";
    cout << "   -----------------------------------------------\n";
    if (!jenis.empty())
        cout << "\tJenis : " << jenis << "\n";
    if (!merk.empty())
        cout << "\tMerk  : " << merk << "\n\n";
}

void menuFilterBarang()
{
    string fJenis, fMerk;
    int hMin = 0, hMax = 99999999;

    clearBuffer();
    bersihkanLayar();
    printGoRent();
    cout << "\n";
    cout << "   -----------------------------------------------\n";
    cout << "   |              F I L T E R  B A R A N G         |\n";
    cout << "   -----------------------------------------------\n";

    do
    {
        cout << "   Masukkan Jenis (Motor/Mobil) : ";
        getline(cin, fJenis);
        string cekJenis = fJenis;
        for (char &c : cekJenis)
            c = tolower(c);

        if (cekJenis == "motor")
        {
            fJenis = "motor";
            break;
        }
        if (cekJenis == "mobil")
        {
            fJenis = "mobil";
            break;
        }
        cout << RED << "   [!] Input salah! Masukkan Motor atau Mobil" << RESET << endl;
    } while (true);

    cout << "   Masukkan Merk                : ";
    getline(cin, fMerk);
    string fMerkLower = fMerk;
    for (char &c : fMerkLower)
        c = tolower(c);

    const int TOTAL_MENU = 4;
    string menuHarga[TOTAL_MENU] = {
        "Rp 0 - Rp 100.000",
        "Rp 100.001 - Rp 200.000",
        "Rp 200.001 - Rp 500.000",
        "Tampilkan Semua Harga"};
    int pilihHarga = 0;
    char key;

    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n   -----------------------------------------------" << endl;
        cout << "   |         PILIH RENTANG HARGA PER HARI         |" << endl;
        cout << "   -----------------------------------------------" << endl;
        cout << endl;
        for (int i = 0; i < TOTAL_MENU; i++)
        {
            cout << (i == pilihHarga ? BLUE "           >> " : "              ") << menuHarga[i] << RESET << endl;
            cout << endl;
        }
        cout << "   ===============================================" << endl;

        key = _getch();
        if (key == 224 || key == -32)
        {
            key = _getch();
            if (key == 72)
                pilihHarga = (pilihHarga == 0) ? TOTAL_MENU - 1 : pilihHarga - 1;
            else if (key == 80)
                pilihHarga = (pilihHarga == TOTAL_MENU - 1) ? 0 : pilihHarga + 1;
        }
    } while (key != 13);

    switch (pilihHarga)
    {
    case 0:
        hMin = 0;
        hMax = 100000;
        break;
    case 1:
        hMin = 100001;
        hMax = 200000;
        break;
    case 2:
        hMin = 200001;
        hMax = 500000;
        break;
    case 3:
        hMin = 0;
        hMax = 99999999;
        break;
    }

    bersihkanLayar();
    printGoRent();
    cout << "\n   -----------------------------------------------" << endl;
    cout << "   |             HASIL FILTER BARANG             |" << endl;
    cout << "   -----------------------------------------------" << endl;

    bool ditemukan = false;
    int nomor = 1;

    for (int i = 0; i < jumlahBarang; i++)
    {
        string descLower = daftarBarang[i].deskripsi;
        for (char &c : descLower)
            c = tolower(c);

        if ((descLower.find(fJenis) != string::npos) &&
            (descLower.find(fMerkLower) != string::npos) &&
            (daftarBarang[i].harga >= hMin && daftarBarang[i].harga <= hMax))
        {
            cout << "   " << nomor++ << ". Nama      : " << daftarBarang[i].nama << endl;
            cout << "\n      Harga      : Rp" << daftarBarang[i].harga << endl;
            cout << "\n      Status     : " << (daftarBarang[i].available ? "Tersedia" : "Sedang Disewa") << endl;
            cout << "\n      Deskripsi  : " << daftarBarang[i].deskripsi << endl;
            cout << "\n      " << BLUE << "\033]8;;" << daftarBarang[i].url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
            cout << "   -----------------------------------------------" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan)
        cout << RED << "\n   [!] Tidak ada kendaraan yang cocok dengan kriteria." << RESET << endl;

    cin.clear();
    jedaTampilan();
}

void bubbleSortHarga(bool ascending)
{
    for (int i = 0; i < jumlahBarang - 1; i++)
    {
        for (int j = 0; j < jumlahBarang - i - 1; j++)
        {
            if ((ascending && daftarBarang[j].harga > daftarBarang[j + 1].harga) ||
                (!ascending && daftarBarang[j].harga < daftarBarang[j + 1].harga))
            {
                Barang temp = daftarBarang[j];
                daftarBarang[j] = daftarBarang[j + 1];
                daftarBarang[j + 1] = temp;
            }
        }
    }
}

void menuSortirBarang()
{
    int key;
    int pilihSortir = 0;
    const int TOTAL_MENU = 3;

    string menu[] = {
        "Harga Termurah -> Termahal ",
        "Harga Termahal -> Termurah ",
        "Kembali"};
    clearBuffer();
    do
    {
        bersihkanLayar();
        printGoRent();
        cout << "\n";
        cout << "   -----------------------------------------------\n";
        cout << "   |           S O R T I R  B A R A N G           |\n";
        cout << "   -----------------------------------------------\n";
        cout << endl;
        for (int i = 0; i < TOTAL_MENU; i++)
        {
            if (i == pilihSortir)
            {
                cout << BLUE << "\t    >> " << menu[i] << RESET << endl;
                cout << endl;
            }
            else
            {
                cout << "\t       " << menu[i] << endl;
                cout << endl;
            }
        }
        cout << "   ===============================================\n";
        key = _getch();

        if (key == 224)
        {
            key = _getch();
            if (key == 72)
                pilihSortir = (pilihSortir == 0) ? TOTAL_MENU - 1 : pilihSortir - 1;
            else if (key == 80)
                pilihSortir = (pilihSortir == TOTAL_MENU - 1) ? 0 : pilihSortir + 1;
        }

    } while (key != 13);

    switch (pilihSortir)
    {
    case 0:
        bubbleSortHarga(true);
        break;
    case 1:
        bubbleSortHarga(false);
        break;
    case 2:
        return;
    }

    bersihkanLayar();
    cout << "\n";
    cout << "   -----------------------------------------------\n";
    cout << "   |          H A S I L  S O R T I R              \n";
    cout << "   -----------------------------------------------\n";
    if (jumlahBarang == 0)
    {
        cout << "\t     [ Tidak ada kendaraan yang tersedia ]\n";
    }
    else
    {
        for (int i = 0; i < jumlahBarang; i++)
        {
            cout << "\n   " << i + 1 << ". Nama       : " << daftarBarang[i].nama << endl;
            cout << "\n      Harga      : Rp" << daftarBarang[i].harga << endl;
            cout << "\n      Status     : " << (daftarBarang[i].available ? "Tersedia" : "Sedang Disewa") << endl;
            cout << "\n      Deskripsi  : " << daftarBarang[i].deskripsi << endl;
            cout << "\n      " << BLUE << "\033]8;;" << daftarBarang[i].url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
            cout << "\n   -----------------------------------------------" << endl;
        }
    }

    jedaTampilan();
}

void cariBarang()
{
    clearBuffer();
    bersihkanLayar();
    printGoRent();
    string keyword;
    cout << "\n   -----------------------------------------------\n";
    cout << "   |             C A R I  B A R A N G            |\n";
    cout << "   -----------------------------------------------\n";
    cout << "   Masukkan nama barang yang dicari: ";
    getline(cin, keyword);
    cout << "   ===============================================\n";
    cout << "   Hasil pencarian untuk: \"" << keyword << "\"\n";
    cout << "   -----------------------------------------------\n";

    bool ditemukan = false;
    int nomor = 1;

    for (int i = 0; i < jumlahBarang; i++)
    {
        string nama = daftarBarang[i].nama;
        int n = nama.length();
        int m = keyword.length();
        bool cocok = false;

        for (int j = 0; j <= n - m; j++)
        {
            int k;
            for (k = 0; k < m; k++)
            {
                if (tolower(nama[j + k]) != tolower(keyword[k]))
                    break;
            }
            if (k == m)
            {
                cocok = true;
                break;
            }
        }

        if (cocok)
        {
            cout << "   " << nomor << ". Nama      : " << daftarBarang[i].nama << endl;
            cout << "\n      Harga      : Rp" << daftarBarang[i].harga << endl;
            cout << "\n      Status     : " << (daftarBarang[i].available ? "Tersedia" : "Sedang Disewa") << endl;
            cout << "\n      Deskripsi  : " << daftarBarang[i].deskripsi << endl;
            cout << "\n      " << BLUE << "\033]8;;" << daftarBarang[i].url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
            cout << "   -----------------------------------------------\n";

            ditemukan = true;
            nomor++;
        }
    }

    if (!ditemukan)
        cout << "\n   [!] Barang tidak ditemukan.\n";
    jedaTampilan();
}

int main()
{
    inisialisasiDummyData();
    dataAwal();
    menuUtama();
    return 0;
}