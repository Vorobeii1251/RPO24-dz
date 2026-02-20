from PySide6.QtWidgets import QWidget, QVBoxLayout, QLabel, QPushButton, QHBoxLayout, QFrame
from PySide6.QtCore import Signal, Qt
from PySide6.QtGui import QFont


class TrackWidget(QWidget):
    track_selected = Signal(str, str, str)

    def __init__(self, track_name, artist, genre, parent=None):
        super().__init__(parent)

        self.track_name = track_name
        self.artist = artist
        self.genre = genre

        self.init_ui()

    def init_ui(self):
        main_layout = QHBoxLayout()
        main_layout.setContentsMargins(10, 10, 10, 10)

        frame = QFrame()
        frame.setFrameStyle(QFrame.Box | QFrame.Raised)
        frame.setLineWidth(1)

        frame_layout = QHBoxLayout(frame)

        info_layout = QVBoxLayout()

        title_label = QLabel(self.track_name)
        title_font = QFont()
        title_font.setBold(True)
        title_font.setPointSize(12)
        title_label.setFont(title_font)

        artist_label = QLabel(f"Исполнитель: {self.artist}")

        genre_label = QLabel(f"Жанр: {self.genre}")

        info_layout.addWidget(title_label)
        info_layout.addWidget(artist_label)
        info_layout.addWidget(genre_label)
        info_layout.addStretch()

        button_layout = QVBoxLayout()

        self.select_button = QPushButton("🎵 Выбрать")
        self.select_button.setMinimumHeight(40)
        self.select_button.setMinimumWidth(100)

        self.select_button.clicked.connect(self.on_select_clicked)

        button_layout.addStretch()
        button_layout.addWidget(self.select_button)
        button_layout.addStretch()

        frame_layout.addLayout(info_layout, 3)
        frame_layout.addLayout(button_layout, 1)

        main_layout.addWidget(frame)

        self.setLayout(main_layout)

        self.setMinimumHeight(100)

    def on_select_clicked(self):
        self.track_selected.emit(self.track_name, self.artist, self.genre)

    def get_track_info(self):
        return {
            'track': self.track_name,
            'artist': self.artist,
            'genre': self.genre
        }