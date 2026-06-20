#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX = 100;

struct Account{
    string username;
    string password;
};

Account admin[1];
Account user[MAX];

int jumlahUser = 2;

//================ DATA AWAL =================
void dataAwal()
{
    admin[0].username = "admin";
    admin[0].password = "admin123";

    user[0].username = "user1";
    user[0].password = "123";

    user[1].username = "user2";
    user[1].password = "456";
}

//============== BERSIHKAN LAYAR =============
void bersihkanLayar()
{
    system("cls");
}
void jedaTampilan() {
	cout << ">> Tekan ENTER untuk pulse berikutnya...";
	cin.ignore();
	cin.get();
}

void banner(){
cout << "\033[38;2;0;0;0m";
cout << R"(
▄▄▄ ▄ ▄▄▄ ▄▄▄ ▄▄▄ ▄▄ ▄     ▄▄  ▄▄▄ ▄▄  ▄▄▄ ▄▄  ▄      ▄ ▄ ▄▄▄ ▄▄  ▄▄  ▄▄  ▄▄  ▄▄  ▄▄  ▄▄      
▀▄  █ ▀▄   █  █▄  █ █ █    █▄▀ █▄  █ █  █  █▄█ █      █▄▀ █▄  █ █ █ █ █▄█ █▄▀ █▄█ █▄█ █ █     
▄▄▀ ▄ ▄▄▀  █  █▄▄ █   █    █ █ █▄▄ █ █  █  █ █ █▄▄    █ █ █▄▄ █ █ █▄▀ █ █ █ █ █ █ █ █ █ █     

)";
cout << "\033[0m";
}

void pembatas() {
	cout << "===============================\n";
}

//============== CEK ADMIN ===================
bool cekAdmin(string username, string password) {
	
    if(username == admin[0].username && 
	password == admin[0].password)
    {
        return true;
    }

    return false;
}

//=============== CEK USER ===================
bool cekUser(string username,string password)
{
    for(int i=0;i<jumlahUser;i++)
    {
        if(username == user[i].username &&
           password == user[i].password)
        {
            return true;
        }
    }

    return false;
}

//=========== CEK USERNAME ===================
bool usernameTerdaftar(string username)
{
	if(username == admin[0].username) {
		return true;
	}
    for(int i=0;i<jumlahUser;i++)
    {
        if(username == user[i].username)
        {
            return true;
        }
    }

    return false;
}

//============= LOGIN ADMIN ==================
void loginAdmin(){
    bersihkanLayar();
    string username,password;
	cout << "===============================\n";
    cout << "|      LOGIN ADMIN            |\n";
    cout << "===============================\n";

    cout << "Username : ";
    cin >> username;

    cout << "Password : ";
    cin >> password;

    if(cekAdmin(username,password))
    {
    	pembatas();
        cout << "Login Admin Berhasil.\n";
        cout << "Selamat Datang Admin.\n";
        pembatas();
    }
    else
    {
    	pembatas();
        cout << "Username atau Password Salah.\n";
    	pembatas();
    }
    jedaTampilan();
}

//============== LOGIN USER ==================
void loginUser(){
    bersihkanLayar();
    string username,password;
    cout << "===============================\n";
    cout << "|         LOGIN USER          |\n";
    cout << "===============================\n";

    cout << "Username : ";
    cin >> username;

    cout << "Password : ";
    cin >> password;

    if(cekUser(username,password))
    {
    	pembatas();
        cout << "\nLogin User Berhasil.\n";
        cout << "Selamat Datang User.\n";
    }
    else
    {
    	pembatas();
        cout << "Username atau Password Salah.\n";
        pembatas();
    }
    jedaTampilan();
}

//================ LOGIN =====================
void login()
{
    int pilih;
	do{
    bersihkanLayar();
    cout << "===============================\n";
    cout << "|             LOGIN           |\n";
    cout << "===============================\n";
    cout << "1. Login sebagai Admin\n";
    cout << "2. Login sebagai User\n";
    cout << "0. Kembali\n";
    pembatas();
    cout << "Pilihan : ";
    cin >> pilih;

    switch(pilih)
    {
        case 1:
            loginAdmin();
            break;

        case 2:
            loginUser();
            break;
            
        case 0:
        	pembatas();
            cout << "Kembbali ke Menu Utama\n";
            break;

        default:
        	pembatas();
            cout<<"Pilihan Tidak Valid.\n";
            jedaTampilan();
        }
    } while(pilih != 0);
}

//============= BIKIN AKUN ===================
void bikinAkun()
{
    bersihkanLayar();
    string username,password,confirm;

    cout << "===============================\n";
    cout << "|      REGISTRASI PENGGUNA    |\n";
    cout << "===============================\n";

    cout << "Username : ";
    cin >> username;

    if(usernameTerdaftar(username))
    {
    	pembatas();
        cout <<"Username sudah digunakan.\n";
        pembatas();
        jedaTampilan() ;
        return;
    }

    cout << "Password : ";
    cin >> password;

    cout << "Confirm Password : ";
    cin >> confirm;

    if(password != confirm)
    {
      	pembatas();
        cout << "Konfirmasi Password Tidak Sama.\n";
    	pembatas();
        jedaTampilan() ;
        return;
    }

    user[jumlahUser].username = username;
    user[jumlahUser].password = password;
    jumlahUser++;
	pembatas();
    cout << "Akun Berhasil Dibuat.\n";
    pembatas();
    jedaTampilan() ;
}

//============== MENU UTAMA ==================
void menuUtama()
{
    int pilihan;

    do{
        bersihkanLayar();
		banner();
         cout << "===============================\n";
 		 cout << "|   SISTEM RENTAL KENDARAAN   |\n";
         cout << "===============================\n";
        cout << "1. Login\n";
        cout << "2. Registrasi Pengguna\n";
        cout << "0. Keluar\n";
        pembatas();
        cout << "Pilihan : ";
        cin >> pilihan;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');

            cout << "\nInput harus berupa angka!\n";
            jedaTampilan() ;
            continue;
        }
        switch(pilihan){
            case 1:
                login();
                break;

            case 2:
                bikinAkun();
                break;

            case 0:
            	pembatas();
                cout<<"Terima Kasih.\n";
                pembatas();
                break;

            default:
                pembatas();
                cout << "Pilihan Tidak Valid!\n";
                cout << "Silakan Pilih Menu yang Tersedia.\n";
                pembatas();
                jedaTampilan() ;
        }

    }while(pilihan!=0);
}

//=================== MAIN ===================
int main()
{
    dataAwal();
    menuUtama();

    return 0;
}