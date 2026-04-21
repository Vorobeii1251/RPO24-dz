#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Track {
protected:
    string title;
    int duration;

public:
    Track(string title, int duration) {
        this->title = title;
        this->duration = duration;
    }

    virtual void play() {
        cout << "Играет трек: " << title << endl;
    }

    virtual int getDuration() const {
        return duration;
    }

    string getTitle() const {
        return title;
    }

    virtual ~Track() {}
};

class Song : public Track {
private:
    string artist;

public:
    Song(string title, int duration, string artist)
        : Track(title, duration) {
        this->artist = artist;
    }

    void play() override {
        cout << "Играет песня: " << title << " - " << artist << endl;
    }

    string getArtist() const {
        return artist;
    }
};

class Instrumental : public Track {
private:
    string instrument;

public:
    Instrumental(string title, int duration, string instrument)
        : Track(title, duration) {
        this->instrument = instrument;
    }

    void play() override {
        cout << "Играет инструментал: " << title
             << " (" << instrument << ")" << endl;
    }

    string getInstrument() const {
        return instrument;
    }
};

class Podcast : public Track {
private:
    string host;
    string topic;

public:
    Podcast(string title, int duration, string host, string topic)
        : Track(title, duration) {
        this->host = host;
        this->topic = topic;
    }

    void play() override {
        cout << "Играет подкаст: " << title
             << " (ведущий: " << host << ", тема: " << topic << ")" << endl;
    }

    string getHost() const {
        return host;
    }

    string getTopic() const {
        return topic;
    }
};

bool compareByTitle(const Track* a, const Track* b) {
    return a->getTitle() < b->getTitle();
}

bool compareByDuration(const Track* a, const Track* b) {
    return a->getDuration() < b->getDuration();
}

string formatDuration(int seconds) {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    string result = to_string(minutes) + ":";
    if (secs < 10) result += "0";
    result += to_string(secs);
    return result;
}

void showAllTracks(const vector<Track*>& playlist) {
    if (playlist.empty()) {
        cout << "\nПлейлист пуст\n";
        return;
    }

    cout << "ВАШ ПЛЕЙЛИСТ (" << playlist.size() << " треков):\n";

    for (size_t i = 0; i < playlist.size(); i++) {
        cout << i + 1 << ". ";
        playlist[i]->play();
        cout << "Длительность: " << formatDuration(playlist[i]->getDuration()) << "\n";
    }
}

void playAllTracks(const vector<Track*>& playlist) {
    if (playlist.empty()) {
        cout << "\nНет треков для воспроизведения\n";
        return;
    }

    cout << "\nвоспроизводится\n";

    for (auto track : playlist) {
        track->play();
    }

    cout << "Воспроизведение завершено\n";
}

void showTotalDuration(const vector<Track*>& playlist) {
    if (playlist.empty()) {
        cout << "\nНет треков для подсчёта\n";
        return;
    }

    int total = 0;
    for (auto track : playlist) {
        total += track->getDuration();
    }

    cout << "\nОбщая длительность плейлиста: " << formatDuration(total) << "\n";
}

void sortTracks(vector<Track*>& playlist, int choice) {
    if (playlist.empty()) {
        cout << "\nНет треков для сортировки\n";
        return;
    }

    if (choice == 1) {
        sort(playlist.begin(), playlist.end(), compareByTitle);
        cout << "\nОтсортировано по НАЗВАНИЮ!\n";
    } else if (choice == 2) {
        sort(playlist.begin(), playlist.end(), compareByDuration);
        cout << "\nОтсортировано по ДЛИТЕЛЬНОСТИ!\n";
    }
}

void cleanupPlaylist(vector<Track*>& playlist) {
    for (auto track : playlist) {
        delete track;
    }
    playlist.clear();
}

void showMenu() {
    cout << "Музыкальный че то там\n";
    cout << "1. Добавить песню\n";
    cout << "2. Добавить инструментал\n";
    cout << "3. Добавить подкаст\n";
    cout << "4. Показать все треки\n";
    cout << "5. Воспроизвести все треки\n";
    cout << "6. Сортировать по названию\n";
    cout << "7. Сортировать по длительности\n";
    cout << "8. Показать общую длительность\n";
    cout << "9. Очистить плейлист\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

string inputString(const string& prompt) {
    string value;
    cout << prompt;
    cin.ignore();
    getline(cin, value);
    return value;
}

int inputInt(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;
    return value;
}

int main() {
    vector<Track*> playlist;
    int choice;

    playlist.push_back(new Song("Believer", 203, "Imagine Dragons"));
    playlist.push_back(new Instrumental("Chill Beat", 180, "Piano"));
    playlist.push_back(new Song("Blinding Lights", 200, "The Weeknd"));
    playlist.push_back(new Podcast("Tech Talk", 3600, "John Doe", "Future of AI"));

    cout << "\nДарова емае как ты? если че это музыкальный че то там\n";

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                {
                    string title = inputString("Введите название песни: ");
                    int duration = inputInt("Введите длительность (секунды): ");
                    string artist = inputString("Введите имя исполнителя: ");
                    playlist.push_back(new Song(title, duration, artist));
                    cout << "Песня добавлена!\n";
                }
                break;
            }

            case 2: {
                {
                    string title = inputString("Введите название инструментала: ");
                    int duration = inputInt("Введите длительность (секунды): ");
                    string instrument = inputString("Введите основной инструмент: ");
                    playlist.push_back(new Instrumental(title, duration, instrument));
                    cout << "Инструментал добавлен!\n";
                }
                break;
            }

            case 3: {
                {
                    string title = inputString("Введите название подкаста: ");
                    int duration = inputInt("Введите длительность (секунды): ");
                    string host = inputString("Введите имя ведущего: ");
                    string topic = inputString("Введите тему подкаста: ");
                    playlist.push_back(new Podcast(title, duration, host, topic));
                    cout << "Подкаст добавлен\n";
                }
                break;
            }

            case 4:
                showAllTracks(playlist);
                break;

            case 5:
                playAllTracks(playlist);
                break;

            case 6:
                sortTracks(playlist, 1);
                showAllTracks(playlist);
                break;

            case 7:
                sortTracks(playlist, 2);
                showAllTracks(playlist);
                break;

            case 8:
                showTotalDuration(playlist);
                break;

            case 9:
                cleanupPlaylist(playlist);
                cout << "Плейлист очищен\n";
                break;

            case 0: // Выход
                cout << "\n Пока малой(ая)\n";
                break;

            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);

    cleanupPlaylist(playlist);

    return 0;
}
