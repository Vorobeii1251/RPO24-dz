from PySide6.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QLabel, QTextEdit, QScrollArea, QMessageBox
from PySide6.QtCore import Qt
from PySide6.QtGui import QFont
from track_widget import TrackWidget


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Музыкальный плеер - Выбор треков")
        self.setGeometry(100, 100, 600, 500)

        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        main_layout = QVBoxLayout(central_widget)

        title_label = QLabel("Выберите трек для прослушивания")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title_label.setFont(title_font)
        title_label.setAlignment(Qt.AlignCenter)
        main_layout.addWidget(title_label)

        scroll_area = QScrollArea()
        scroll_widget = QWidget()
        scroll_layout = QVBoxLayout(scroll_widget)

        tracks = [
            ("белый 500", "Нурминский", "реп"),
            ("в тонере по госту", "Татарин", "пусть будет поп"),
            ("криминал", "n1nt3nd0", "реп"),
            ("со лбом затянута карета", "диман брюханов", "реп"),
            ("голова чтобы думать", "25/17", "реп"),
            ("исполняющий отдел", "lustova", "поп"),
            ("пряталась в ванной", "мари краймбрери", "поп"),
            ("крузак 200", "bodiev", "реп")
        ]

        for track_name, artist, genre in tracks:
            track_widget = TrackWidget(track_name, artist, genre)
            track_widget.track_selected.connect(self.on_track_selected)
            scroll_layout.addWidget(track_widget)

        scroll_layout.addStretch()

        scroll_area.setWidget(scroll_widget)
        scroll_area.setWidgetResizable(True)

        main_layout.addWidget(scroll_area)

        self.info_display = QTextEdit()
        self.info_display.setMaximumHeight(100)
        self.info_display.setReadOnly(True)
        self.info_display.setPlaceholderText("Здесь появится информация о выбранном треке...")
        main_layout.addWidget(self.info_display)

    def on_track_selected(self, track_name, artist, genre):
        message = f"Вы выбрали трек:\n\n"
        message += f"Название: {track_name}\n"
        message += f"Исполнитель: {artist}\n"
        message += f"Жанр: {genre}"

        self.info_display.setText(message)

        QMessageBox.information(
            self,
            "Трек выбран",
            f"Трек '{track_name}' добавлен в плейлист!"
        )