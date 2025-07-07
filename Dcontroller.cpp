#include "Dcontroller.h"

void Dcontroller::LoadFile() 
{
    fstream fs;
    fs.open("data.txt", fstream::in);
    if(!fs.is_open()) 
    {
        cout<<"file not found"<<endl;
        exit(1);
    }
    while(!fs.eof()) 
    {
        student person;
        string str;
        getline(fs, str, '|');
        if(str[0]=='\0') 
        {
            break;
        }
        if(str.find('\n')!=-1)
        {
            str.erase(str.begin());
        }
        person.last_name = str;
        getline(fs, str, '|'); person.name = str;
        getline(fs, str, '|'); person.patronymic = str;
        getline(fs, str, '|'); person.birth_date = str;
        getline(fs, str, '|'); person.arrival_year = str;
        getline(fs, str, '|'); person.faculty = str;
        getline(fs, str, '|'); person.department = str;
        getline(fs, str, '|'); person.group = str;
        getline(fs, str, '|');
        if(FreeId(str)) 
        {
            string id = str;
            Results r;
            getline(fs, str, '|');
            getline(fs, str, '|');
            r.number_of_s = str;
            for(int i = 0; i < 10; i++) 
            {
                getline(fs, str, '|');
                r.subjects.push_back(str);
                getline(fs, str, '|');
                str.resize(1);
                r.marks.push_back(str);
            }
            GetStudent(id).results.push_back(r);
            continue;
        }
        person.markbook_num = str;
        getline(fs, str, '|');
        person.gender = str;
        getline(fs, str, '|');
        Results r;
        r.number_of_s = str;
        for(int i = 0; i < 10; i++) 
        {
            getline(fs, str, '|');
            r.subjects.push_back(str);
            getline(fs, str, '|');
            str.resize(1);
            r.marks.push_back(str);
        }
        person.results.push_back(r);
        data.push_back(person);
    }
    Update();
    fs.close();
}

void Dcontroller::Update() 
{
    fstream fs;
    fs.open("data.txt", fstream::out);
    for(int i = 0; i < data.size();i++) 
    {
        for(int j = 0; j < data[i].results.size();j++) 
        {
            fs << data[i].last_name << "|" << data[i].name << "|" 
            << data[i].patronymic << "|" << data[i].birth_date << "|" 
            << data[i].arrival_year << "|" << data[i].faculty << "|" 
            << data[i].department << "|" << data[i].group << "|" 
            << data[i].markbook_num << "|" << data[i].gender << "|"
            << data[i].results[j].number_of_s<<"|";
            for(int k = 0; k < 10; k++) 
            {
                fs << data[i].results[j].subjects[k] << "|" << data[i].results[j].marks[k]<<"|";
            }
            if(j != data[i].results.size() - 1)
                fs << "\n";
        }
        if(i != data.size() - 1)
            fs << "\n";
    }    
}

bool Dcontroller::FreeId(string id) 
{
    for(int i = 0; i < data.size(); i++) 
    {
        if(data[i].markbook_num==id) 
        {
            return true;
        }
    }
    return false;   
}

student& Dcontroller::GetStudent(string id) 
{
    if(!data.empty()) 
    {
        for(int i = 0;i < data.size(); i++) 
        {
            if(data[i].markbook_num==id) 
            {
                return data[i];
            }
        }
    }
    return data[0];
}

void Dcontroller::Show() 
{
    for(int i = 0; i < data.size(); i++) 
    {
        cout << data[i].last_name << " "  << data[i].name << " " 
        << data[i].patronymic << " " << data[i].birth_date << " " 
        << data[i].arrival_year << " " << data[i].faculty << " " 
        << data[i].department << " "  << data[i].group << " " 
        << data[i].markbook_num << " " << data[i].gender <<endl;
    }
    cout<<endl;    
}

void Dcontroller::Add() 
{
    student person;
    string str;
    cout<<"Новая запись о студенте."<<endl;
    cout<<"Введите Фамилию: ";
    cin>>str; person.last_name = str;
    cout<<"Введите Имя: ";
    cin>>str; person.name = str;
    cout<<"Введите Отчество: ";
    cin>>str; person.patronymic = str;
    cout<<"Введите Дату рождения: ";
    cin>>str; person.birth_date = str;
    cout<<"Введите Дату поступления в университет: ";
    cin>>str; person.arrival_year = str;
    cout<<"Введите Факультет: ";
    cin>>str; person.faculty = str;
    cout<<"Введите Кафедру: ";
    cin>>str; person.department = str;
    cout<<"Введите Группу: ";
    cin>>str; person.group = str;
    cout<<"Введите Номер зачетной книжки: ";
    cin>>str;
    while(FreeId(str)) 
    {
        cout<<"Студент с таким номером зачетной книги уже существует. Введите Номер зачетной книжки: "<<endl;
        cin>>str;
    }
    person.markbook_num = str;
    cout<<"Выберите пол: 1) М. 2) Ж."<<endl; cin>>str;
    while(str!="1" && str!="2") 
    {
        cout<<"Ошибка"<<endl<<"Выберите пол 1) М. 2) Ж."<<endl;
        cin>>str;
    }
    person.gender = "male";
    if(str=="2") 
    {
        person.gender = "female";
    }
    cout<<"Добавление информации о сессии."<<endl<<"1) Добавить предметы и оценки сейчас 2) Добавить позже"<<endl;
    cin>>str;
    while(str!="1" && str!="2") 
    {
        cout<<"Ошибка"<<endl<<"1) Добавить предметы и оценки сейчас 2) Добавить позже"<<endl;
        cin>>str;
    }
    Results r;
    int n;
    cout<<"Номер сессии от 1 до 9: "<<endl;
    cin >> n;
    while(!(n>=1 && n <=9)) 
    {
        cout<<"Ошибка. Номер сессии от 1 до 9: "<<endl;
        cin >> n;
    }
    r.number_of_s = n;
    if(str=="1") {
        cout<<"Предмет оценка. Пример: somename 5."<<endl;
        for(int i = 0;i < 10; i++) 
        {
            string sub;
            int m;
            cin>>sub>>m;
            while(!(m > 2 && m < 6)) 
            {
                cout<<"Ошибка. Оценка должна быть от 3 до 5. Предмет оценка. Пример: subject 4."<<endl;
                cin>>sub>>m;
            }
            r.subjects.push_back(sub);
            r.marks.push_back(to_string(m));
        }
    }
    else {
        for(int i = 0; i < 10; i++) {
            r.subjects.push_back("null");
            r.marks.push_back("0");
        }
    }
    data.push_back(person);
    Update();    
}

void Dcontroller::Edit() 
{
    cout<<"Введите личный номер зачетной книжки студента: "<<endl;
    string id;
    cin>>id;
    if(FreeId(id)) 
    {
        int n;
        cout <<"Редактировать: 1) Фамилия 2) Имя 3) Отчество 4) Д/р Год поступления 6) Факультет 7)Кафедра 8) Группа 9) Номер зачетной книжки 10) Пол\n";
        cin >> n;
        string str;
        switch(n) 
        {
            case 1:
                cout<<"Введите Фамилию: "; cin>>str;
                GetStudent(id).last_name = str;
                break;
            case 2:
                cout<<"Введите Имя: "; cin>>str;
                GetStudent(id).name = str;
                break;
            case 3:
                cout<<"Введите Отчество: "; cin>>str;
                GetStudent(id).patronymic = str;
                break;
            case 4:
                cout<<"Введите Дату рождения: "; cin>>str;
                GetStudent(id).birth_date = str;
                break;
            case 5:
                cout<<"Введите Год поступления: "; cin>>str;
                GetStudent(id).arrival_year = str;
                break;
            case 6:
                cout<<"Введите Факультет: "; cin>>str;
                GetStudent(id).faculty = str;
                break;
            case 7:
                cout<<"Введите Кафедру: "; cin>>str;
                GetStudent(id).department = str;
                break;
            case 8:
                cout<<"Введите Группу: "; cin>>str;
                GetStudent(id).group = str;
                break;
            case 9:
                cout<<"Введите Номер зачетной книжки: "; cin>>str;
                while(FreeId(str)) 
                {
                    cout<<"Ошибка. Студент с таким номером зачетной книги уже существует. Введите Номер зачетной книжки: "<<endl;
                    cin>>str;
                }
                GetStudent(id).markbook_num = str;
                break;
            case 10:
                cout<<"Выберите пол: 1) М. 2) Ж."<<endl;
                int opt;
                cin>>opt;
                while(opt!=1 && opt!=2) 
                {
                    cout<<"Ошибка"<<endl<<"Выберите пол 1) М. 2) Ж."<<endl;
                    cin>>opt;
                }
                GetStudent(id).gender = "male";
                if(opt==2) 
                {
                    GetStudent(id).gender = "female";
                }
                break;
            default:
                cout<<"Ошибка: выбрана неверная опция"<<endl;
        }
    }
    else
    {
         cout<<"Студент не найден"<<endl;
    }
    Update();    
}

void Dcontroller::Delete()
{
    cout<<"Введите номер зачетной книжки студента: "<<endl;
    string id; cin>>id;
    for(int i = 0; i < data.size();i++) 
    {
        if(data[i].markbook_num==id) 
        {
            data.erase(data.begin()+i);
        }
    }
    Update();    
}

void Dcontroller::AddRes()
{
    cout<<"Введите номер зачетной книжки студента: "<<endl;
    string id;
    cin>>id;
    if(FreeId(id)) 
    {
        string s;
        Results r;
        cout<<"Введите номер сессии"<<endl;
        cin>>s;
        r.number_of_s=s;
        cout<<"Предмет оценка. Пример: somename 5."<<endl;
        for(int i = 0;i < 10; i++) 
        {
            string sub;
            int mark;
            cin>>sub>>mark;
            while(!(mark > 2 && mark < 6)) 
            {
                cout<<"Ошибка. Оценка должна быть от 3 до 5. Пример: somename 5."<<endl;
                cin>>sub>>mark;
            }
            r.subjects.push_back(sub);
            r.marks.push_back(to_string(mark));
        }
        GetStudent(id).results.push_back(r);
    }
    else 
    {
        cout<<"Студент не найден"<<endl;
    }
    Update();    
}

void Dcontroller::EditRes()
{
    cout<<"Введите номер зачетной книжки студента: "<<endl;
    string id;
    cin>>id;
    if(FreeId(id)) 
    {
        for(int i = 0; i < GetStudent(id).results.size();i++) 
        {
            cout<<"Сесси "<<GetStudent(id).results[i].number_of_s<<") ";
            for(int j = 0; j < 10; j++) 
            {
                cout<<j+1<<") "<<GetStudent(id).results[i].subjects[j]<< " - "<<GetStudent(id).results[i].marks[j]<< " ";
            }
            cout<<endl;
        }
        cout<<"Введите номер сессии для редактирования: "<<endl;
        string n;
        cin>>n;
        int flag = 0;
        for(int i = 0; i < GetStudent(id).results.size();i++) 
        {
            if(GetStudent(id).results[i].number_of_s == n) 
            {
                flag = 1;
                cout<<"Введите номер предмета: "<<endl;
                int p;
                cin>>p;
                while(!(p > 0 && p < 11)) 
                {
                    cout<<"Неверный номер. Введите номер предмета: "<<endl;
                    cin>>p; 
                }
                cout<<"Предмет оценка. Пример: somename 5."<<endl;
                string sub;
                int m;
                cin>>sub>>m;
                while(!(m > 2 && m < 6)) 
                {
                    cout<<"Ошибка. Оценка должна быть от 3 до 5. Пример: somename 5."<<endl;
                    cin>>sub>>m;
                }
                GetStudent(id).results[i].subjects[p-1] = sub;
                GetStudent(id).results[i].marks[p-1] = to_string(m);
            }
        }
        if(!flag) 
        {
            cout<<"Cессия не найдена"<<endl;
        }
    }
    else 
    {
        cout<<"Студент не найден"<<endl;
    }
    Update();    
}

void Dcontroller::CalculateAll() 
{
    for(int i = 0; i < data.size(); i++) 
    {
        for(int j = 0; j < data[i].results.size(); j++) 
        {
            float summa = 0;
            float n = 0;
            for(int k = 0; k < 10; k++) 
            {
                if(data[i].results[j].marks[k]=="3") 
                {
                    summa+=3;
                }
                if(data[i].results[j].marks[k]=="4") 
                {
                    summa+=4;
                }
                if(data[i].results[j].marks[k]=="5") 
                {
                    summa+=5;
                }
                n++;
            }
            data[i].results[j].average_result = summa/n;
        }
    }    
}


void Dcontroller::CalculateAllTotal() {
    CalculateAll();
    for(int i = 0; i < data.size(); i++)
    {
        float summa = 0;
        float n = 0;
        for(int j = 0; j < data[i].results.size(); j++)
        {
            if(data[i].results[j].average_result!=0) 
            {
                summa+=data[i].results[j].average_result;
                n++;
            }
        }
        data[i].average_sess_res = summa/n;
    }
}

float Dcontroller::GetSessionAverage(string id, string num) {
    float ret = 0;
    for(int i = 0; i < GetStudent(id).results.size(); i++) 
    {
        if(GetStudent(id).results[i].number_of_s == num) 
        {
            ret=GetStudent(id).results[i].average_result;
        }
    }
    return ret;
} 

float Dcontroller::GetMultipleSessionAverage(string id, vector<string> num)
{
    float ret = 0;
    int cnt = 0;
    for(int j = 0; j < num.size();j++) 
    {
        if(GetSessionAverage(GetStudent(id).markbook_num, num[j])!=0) {
            cnt++;
            ret+=GetSessionAverage(GetStudent(id).markbook_num, num[j]);
        }
    }
    if(cnt != num.size()) {
        ret = 0;
    }
    return ret/cnt;
}

void Dcontroller::FindBestWorst()
{
    CalculateAll();
    CalculateAllTotal();
    cout<<"Введите интервал года рождения студентов. Пример: 2000 2024"<<endl;
    int year1, year2;
    cin>>year1>>year2;
    vector<student> scope;
    vector<string> nums;
    student Best;
    student Worst;
    float max = 0.0;
    float min = 5.1;
    int flag = 0;
    for(int i = 0; i < data.size(); i++) 
    {
        int target_year = stoi(data[i].birth_date.substr(6, 9));
        if(year2 >= target_year && target_year >= year1) 
        {
            scope.push_back(data[i]);
        }
    }
    if(scope.empty()){
        cout<<"Студенты в заданном диапазоне не найдены"<<endl;
        return;
    }
    cout<<"Введите опцию."<<endl<<"1)распечатать все данные о студентах, которые успевают с наибольшим и наименьшим успехом в одной сессии"<<endl
    <<"2)Распечатать все данные о студентах, которые успевают с наибольшим и наименьшим успехом в нескольких сессиях"<<endl
    <<"3)Распечатать все данные о студентах, которые успевают с наибольшим и наименьшим успехом во всех сессиях"<<endl;

    int opc;
    cin>>opc;
    switch(opc)
    {
    case 1:
    {
        cout<<"Введите номер необходимой сессии от 1 до 9"<<endl;
        int sess;
        cin>>sess;
        for(int i = 0; i < scope.size();i++) 
        {
            if(GetSessionAverage(scope[i].markbook_num, to_string(sess))!=0)
            {   
                flag=1;
                if(GetSessionAverage(scope[i].markbook_num, to_string(sess)) > max) 
                {
                    Best = GetStudent(scope[i].markbook_num);
                    max = GetSessionAverage(scope[i].markbook_num, to_string(sess));
                }
                if(GetSessionAverage(scope[i].markbook_num, to_string(sess)) < min)
                {
                    Worst = GetStudent(scope[i].markbook_num);
                    min = GetSessionAverage(scope[i].markbook_num, to_string(sess));
                }
            }
        }
        if(flag) 
        {
            cout<<"Лучший студент в сессии "<<sess<<": "<<Best<<" Средний балл: "<<max<<endl;
            cout<<"Худший студент в сессии "<<sess<<": "<<Worst<<" Средний балл: "<<min<<endl;  
        }
        else
        {
            cout<<"Не найдены студенты в этом диапазоне, сдавшие эту сессию"<<endl;
        }
        break;
    }
    case 2:
    {
        cout<<"Введите количество сессий от 1 до 9"<<endl;
        int num;
        cin>>num;
        while(!(num>=1 && num <=9)) 
        {
            cout<<"Ошибка. количество сессий от 1 до 9"<<endl;
            cin >> num;
        }
        for(int i = 0; i < num; i++)
        {   
            int sess;
            cout<<"Введите номер сессии от 1 до 9 без повторений"<<endl;
            cin>>sess;
            while(!(sess >=1 && sess <=9) || (find(nums.begin(), nums.end(), to_string(sess))!=nums.end())) 
            {   
                if(find(nums.begin(), nums.end(), to_string(sess))!=nums.end()) {
                    cout<<"Эта сессия уже в списке"<<endl;
                }
                cout<<"Ошибка. Номер сессии от 1 до 9"<<endl;
                cin >> sess;
            }
            nums.push_back(to_string(sess));
        }
        for(int i = 0; i < scope.size(); i++)
        {
            if(GetMultipleSessionAverage(scope[i].markbook_num, nums)!=0)
            {   
                flag=1;
                if(GetMultipleSessionAverage(scope[i].markbook_num, nums) > max) 
                {
                    Best = GetStudent(scope[i].markbook_num);
                    max = GetMultipleSessionAverage(scope[i].markbook_num, nums);
                }
                if(GetMultipleSessionAverage(scope[i].markbook_num, nums) < min)
                {
                    Worst = GetStudent(scope[i].markbook_num);
                    min = GetMultipleSessionAverage(scope[i].markbook_num, nums);
                }
            }
        }
        if(flag) 
        {
            cout<<"Лучший студент в заданных сессиях: "<<Best<<" Средний балл: "<<max<<endl;
            cout<<"Худший студент в заданных сессиях: "<<Worst<<" Средний балл: "<<min<<endl;  
        }
        else
        {
            cout<<"Не найдены студенты в этом диапазоне, сдавшие эти сессии"<<endl;
        }
        break;
    }
    case 3:
    {
        Best = scope[0];
        Worst = scope[0];
        for(int i = 0; i < scope.size(); i++) 
        {
            if(scope[i].average_sess_res >= Best.average_sess_res) 
            {
                Best = scope[i];
            }
            if(scope[i].average_sess_res <= Worst.average_sess_res) 
            {
                Worst = scope[i];
            }
        }
        cout<<"Лучший студент: "<<Best<<" Средний балл: "<<Best.average_sess_res<<endl;
        cout<<"Худший студент: "<<Worst<<" Средний балл: "<<Worst.average_sess_res<<endl;
        break;
    }
    default:
        cout<<"Wrong option"<<endl;
        break;
    }
}

ostream& operator<<(ostream& os, student& st) {
    os << st.last_name << " " 
    << st.name << " " 
    << st.patronymic << " " 
    << st.birth_date << " " 
    << st.arrival_year << " " 
    << st.faculty << " " 
    << st.department << " " 
    << st.group << " " 
    << st.markbook_num << " " 
    << st.gender << "\n";
    return os;
}

ostream& operator<<(ostream& os, Dcontroller& src) {
    for(int i = 0; i <src.data.size(); i++) {
        os << src.data[i].last_name << " "  << src.data[i].name << " " 
        << src.data[i].patronymic << " " << src.data[i].birth_date << " " 
        << src.data[i].arrival_year << " " << src.data[i].faculty << " " 
        << src.data[i].department << " " << src.data[i].group << " " 
        << src.data[i].markbook_num << " " << src.data[i].gender << "\n";
        for(int j = 0; j < src.data[i].results.size(); j++) {
            os << "Сессия: " <<src.data[i].results[j].number_of_s<<" ";
            for(int k = 0; k < 10; k++) {
                os<<k+1<<") "<<src.data[i].results[j].subjects[k]<< " - "<<src.data[i].results[j].marks[k]<< " ";
            }
            os<<endl;
        }
        os<<endl;
    }
    return os;
}