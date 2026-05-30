import 'package:flutter/material.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Заметки',
      home: NotesScreen(),
    );
  }
}

class NotesScreen extends StatefulWidget {
  @override
  _NotesScreenState createState() => _NotesScreenState();
}

class _NotesScreenState extends State<NotesScreen> {
  // Список заметок
  List<Map<String, dynamic>> notes = [
    {'id': 1, 'text': 'Купить молоко', 'favorite': true},
    {'id': 2, 'text': 'Позвонить врачу', 'favorite': false},
    {'id': 3, 'text': 'Сделать домашнее задание', 'favorite': true},
  ];

  // Функция удаления из избранного
  void removeFromFavorites(int noteId) {
    setState(() {
      final note = notes.firstWhere((note) => note['id'] == noteId);
      note['favorite'] = false; // Удаляем из избранного
    });
  }

  // Функция добавления в избранное
  void addToFavorites(int noteId) {
    setState(() {
      final note = notes.firstWhere((note) => note['id'] == noteId);
      note['favorite'] = true;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Мои заметки'),
        backgroundColor: Colors.blue,
      ),
      body: ListView.builder(
        itemCount: notes.length,
        itemBuilder: (context, index) {
          final note = notes[index];
          final isFavorite = note['favorite'];

          return Card(
            margin: EdgeInsets.symmetric(horizontal: 16, vertical: 8),
            child: ListTile(
              title: Text(
                note['text'],
                style: TextStyle(fontSize: 16),
              ),
              trailing: IconButton(
                icon: Icon(
                  isFavorite ? Icons.star : Icons.star_border,
                  color: isFavorite ? Colors.amber : Colors.grey,
                  size: 28,
                ),
                onPressed: () {
                  if (isFavorite) {
                    removeFromFavorites(note['id']); // Удаляем из избранного
                  } else {
                    addToFavorites(note['id']);
                  }
                },
              ),
            ),
          );
        },
      ),
    );
  }
}