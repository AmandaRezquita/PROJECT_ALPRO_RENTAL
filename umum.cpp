#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#define BLUE "\033[34m"
#define RESET "\033[0m"
using namespace std;

const int MAX = 100;

struct Account
{
    string username;
    string password;
};

struct Barang
{
    string url;
    string nama;
    int harga;
    string deskripsi;
    bool available;
};

Account admin[1];
Account user[MAX];
Barang daftarBarang[MAX];
int jumlahUser = 2;
int pilihMenu = 0;
int jumlahBarang = 0;
int edit;
char yesorno;
string tempJenis, tempMerk, tempDeskripsi;

void dashboardAdmin();
void dashboardUser();
void kelolaBarang();
void createBarang();
void readBarang();
void pilih_Barang_Edit();
void deleteBarang();

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

void clearBuffer()
{
    cin.clear();
    cin.ignore(MAX, '\n');
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

void dataAwal()
{
    admin[0].username = "admin";
    admin[0].password = "admin123";
    user[0].username = "user1";
    user[0].password = "123";
    user[1].username = "user2";
    user[1].password = "456";
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
        if (u == user[i].username && p == user[i].password)
            return true;
    }
    return false;
}

bool cekUsername(string u)
{
    if (u == admin[0].username)
        return true;
    for (int i = 0; i < jumlahUser; i++)
    {
        if (u == user[i].username)
            return true;
    }
    return false;
}

void loginAdmin()
{
    bersihkanLayar();
    string u, p;
    cout << endl;
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
        cout << BLUE << "[Login Berhasil!]\n"
             << RESET
             << endl;
        lanjutTampilan();
        dashboardAdmin();
    }
    else
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << "[Login Gagal!]\n"
             << endl;
        jedaTampilan();
    }
}

void loginUser()
{
    bersihkanLayar();
    string u, p;
    cout << endl;
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
        cout << BLUE << "[Login Berhasil!]\n"
             << RESET << endl;
        dashboardUser();
    }
    else
    {
        cout << endl;
        cout << '\t' << "     ";
        cout << "[Login Gagal!]\n"
             << endl;
    }
    jedaTampilan();
}

void registrasi()
{
    bersihkanLayar();
    string u, p, c;
    cout << endl;
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
        cout << "[Username sudah terdaftar!]\n";
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
            user[jumlahUser].username = u;
            user[jumlahUser].password = p;
            jumlahUser++;
            cout << endl;
            cout << '\t' << "     ";
            cout << "[Akun berhasil dibuat!]\n";
        }
        else
        {
            cout << endl;
            cout << '\t' << "     ";
            cout << "[Password tidak cocok!]\n";
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
                cout << "\033[36m>> " << menu[i] << "\033[0m" << endl;
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
        tampilkanVespa();
        cout << '\n';
        cout << "     ===========================================================\n";
        cout << endl;
        cout << "       ";
        cout << "      S I S T E M  R E N T A L  K E N D A R A A N      \n";
        string menu[] = {"Login", "Registrasi", "Keluar"};
        for (int i = 0; i < 3; i++)
        {
            cout << endl;
            cout << '\t' << "     ";

            if (i == pilihMenu)
                cout << "\033[36m>> " << menu[i] << "\033[0m" << endl;
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

    cetakHeaderFilter("", "");
    clearBuffer();

    do
    {
        cout << "\n   Masukkan Jenis (Motor/Mobil) : ";
        getline(cin, fJenis);
        if (fJenis == "motor" || fJenis == "Motor" || fJenis == "MOTOR")
        {
            fJenis = "Motor";
            break;
        }
        if (fJenis == "mobil" || fJenis == "Mobil" || fJenis == "MOBIL")
        {
            fJenis = "Mobil";
            break;
        }
        cout << "   [Input Salah! Masukkan Motor atau Mobil]\n\n";
    } while (true);

    cout << endl;
    while (true)
    {
        cout << "   Masukkan Merk (Honda/dll)    : ";
        getline(cin, fMerk);
        if (fMerk == "honda" || fMerk == "Honda" || fMerk == "HONDA")
        {
            fMerk = "Honda";
            break;
        }
        cout << "   [Input Salah! Hanya tersedia merk Honda]\n\n";
    }

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
        cetakHeaderFilter(fJenis, fMerk);
        cout << "\tPilih Rentang Harga Per Hari (Gunakan Panah + ENTER):\n";

        for (int i = 0; i < TOTAL_MENU; i++)
        {
            if (i == pilihHarga)
                cout << "\t\033[36m>> " << menuHarga[i] << "\033[0m\n";
            else
                cout << "\t   " << menuHarga[i] << "\n";
        }

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
    cout << "\n   ==================== HASIL FILTER ====================\n\n";
    bool ditemukan = false;
    int nomor = 1;

    for (int i = 0; i < jumlahBarang; i++)
    {
        if ((daftarBarang[i].deskripsi.find(fJenis) <= daftarBarang[i].deskripsi.length()) &&
            (daftarBarang[i].deskripsi.find(fMerk) <= daftarBarang[i].deskripsi.length()) &&
            (daftarBarang[i].harga >= hMin && daftarBarang[i].harga <= hMax))
        {
            cout << "\n   " << i + 1 << ". Nama       : " << daftarBarang[i].nama << endl;
            cout << "\n      Harga      : Rp" << daftarBarang[i].harga << endl;
            cout << "\n      Status     : " << (daftarBarang[i].available ? "Tersedia" : "Sedang Disewa") << endl;
            cout << "\n      Deskripsi  : " << daftarBarang[i].deskripsi << endl;
            cout << "\n      " << BLUE << "\033]8;;" << daftarBarang[i].url << "\033\\Foto Produk\033]8;;\033\\" << RESET << endl;
            cout << "\n   -----------------------------------------------" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan)
        cout << "\t     [ Tidak ada kendaraan yang cocok ]\n";
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
        "Kembali"
    };
    
    do
    {
        bersihkanLayar();
        cout << "\n";
        cout << "   -----------------------------------------------\n";
        cout << "   |           S O R T I R  B A R A N G           |\n";
        cout << "   -----------------------------------------------\n";
        cout << endl;
        for (int i = 0; i < TOTAL_MENU; i++)
        {
            if (i == pilihSortir) {
                cout << "\t    \033[36m>> " << menu[i] << "\033[0m" << endl;
                cout << endl;
            } else {
                cout << "\t       " << menu[i] << endl;
                cout << endl;
            }
        }
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
    if (jumlahBarang == 0) {
        cout << "\t     [ Tidak ada kendaraan yang tersedia ]\n";
    } else {
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

int main()
{
    inisialisasiDummyData();
    dataAwal();
    menuUtama();
    return 0;
}