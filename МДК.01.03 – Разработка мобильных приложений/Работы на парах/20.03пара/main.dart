import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Список студентов',
      theme: ThemeData(
        primarySwatch: Colors.blue,
        useMaterial3: true,
      ),
      home: const StudentsApp(),
    );
  }
}

class StudentsApp extends StatefulWidget {
  const StudentsApp({super.key});

  @override
  State<StudentsApp> createState() => _StudentsAppState();
}

class _StudentsAppState extends State<StudentsApp> {
  List<dynamic> _students = [];
  bool _isLoading = true;
  String _sortBy = 'name'; 

  @override
  void initState() {
    super.initState();
    _loadStudents();
  }

  Future<void> _loadStudents() async {
    setState(() => _isLoading = true);
    
    try {
      final response = await http.post(
        Uri.parse('http://localhost/students.php'),
        body: {'action': 'read', 'sort': _sortBy},
      );
      
      if (response.statusCode == 200) {
        final data = jsonDecode(response.body);
        if (data['success']) {
          setState(() {
            _students = data['students'];
            _isLoading = false;
          });
        }
      }
    } catch (e) {
      print('Ошибка загрузки: $e');
      setState(() => _isLoading = false);
    }
  }

  Future<void> _createStudent(String name, String group, String score) async {
    try {
      final response = await http.post(
        Uri.parse('http://localhost/students.php'),
        body: {
          'action': 'create',
          'name': name,
          'group': group,
          'score': score,
        },
      );
      
      if (response.statusCode == 200) {
        final data = jsonDecode(response.body);
        if (data['success']) {
          _loadStudents();
        }
      }
    } catch (e) {
      print('Ошибка добавления: $e');
    }
  }

  Future<void> _updateStudent(int id, String name, String group, String score) async {
    try {
      final response = await http.post(
        Uri.parse('http://localhost/students.php'),
        body: {
          'action': 'update',
          'id': id.toString(),
          'name': name,
          'group': group,
          'score': score,
        },
      );
      
      if (response.statusCode == 200) {
        final data = jsonDecode(response.body);
        if (data['success']) {
          _loadStudents();
        }
      }
    } catch (e) {
      print('Ошибка обновления: $e');
    }
  }

  Future<void> _deleteStudent(int id) async {
    try {
      final response = await http.post(
        Uri.parse('http://localhost/students.php'),
        body: {
          'action': 'delete',
          'id': id.toString(),
        },
      );
      
      if (response.statusCode == 200) {
        final data = jsonDecode(response.body);
        if (data['success']) {
          _loadStudents();
        }
      }
    } catch (e) {
      print('Ошибка удаления: $e');
    }
  }

  void _showDialog({int? id, String? name, String? group, String? score}) {
    final nameController = TextEditingController(text: name);
    final groupController = TextEditingController(text: group);
    final scoreController = TextEditingController(text: score);
    
    showDialog(
      context: context,
      builder: (ctx) => AlertDialog(
        title: Text(id == null ? 'Добавить студента' : 'Редактировать'),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextField(
              controller: nameController,
              decoration: const InputDecoration(
                labelText: 'ФИО',
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 10),
            TextField(
              controller: groupController,
              decoration: const InputDecoration(
                labelText: 'Группа',
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 10),
            TextField(
              controller: scoreController,
              decoration: const InputDecoration(
                labelText: 'Средний балл',
                border: OutlineInputBorder(),
              ),
              keyboardType: TextInputType.number,
            ),
          ],
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(ctx),
            child: const Text('Отмена'),
          ),
          ElevatedButton(
            onPressed: () {
              if (id == null) {
                _createStudent(
                  nameController.text,
                  groupController.text,
                  scoreController.text,
                );
              } else {
                _updateStudent(
                  id,
                  nameController.text,
                  groupController.text,
                  scoreController.text,
                );
              }
              Navigator.pop(ctx);
            },
            child: const Text('Сохранить'),
          ),
        ],
      ),
    );
  }

  void _toggleSort() {
    setState(() {
      _sortBy = _sortBy == 'name' ? 'score' : 'name';
    });
    _loadStudents();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Список студентов'),
        actions: [
          IconButton(
            icon: const Icon(Icons.sort),
            onPressed: _toggleSort,
            tooltip: _sortBy == 'name' 
                ? 'Сортировать по баллу' 
                : 'Сортировать по имени',
          ),
          IconButton(
            icon: const Icon(Icons.refresh),
            onPressed: _loadStudents,
            tooltip: 'Обновить',
          ),
        ],
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => _showDialog(),
        child: const Icon(Icons.add),
      ),
      body: _isLoading
          ? const Center(child: CircularProgressIndicator())
          : ListView.builder(
              itemCount: _students.length,
              itemBuilder: (ctx, index) {
                final student = _students[index];
                return Dismissible(
                  key: Key(student['id'].toString()),
                  background: Container(color: Colors.red),
                  direction: DismissDirection.endToStart,
                  onDismissed: (direction) {
                    _deleteStudent(student['id']);
                  },
                  child: ListTile(
                    title: Text(
                      student['name'],
                      style: const TextStyle(fontWeight: FontWeight.bold),
                    ),
                    subtitle: Text(
                      'Группа: ${student['group']} | Балл: ${student['score']}',
                    ),
                    trailing: Row(
                      mainAxisSize: MainAxisSize.min,
                      children: [
                        IconButton(
                          icon: const Icon(Icons.edit, color: Colors.blue),
                          onPressed: () => _showDialog(
                            id: student['id'],
                            name: student['name'],
                            group: student['group'],
                            score: student['score'].toString(),
                          ),
                        ),
                        IconButton(
                          icon: const Icon(Icons.delete, color: Colors.red),
                          onPressed: () {
                            showDialog(
                              context: context,
                              builder: (ctx) => AlertDialog(
                                title: const Text('Подтверждение'),
                                content: Text('Удалить ${student['name']}?'),
                                actions: [
                                  TextButton(
                                    onPressed: () => Navigator.pop(ctx),
                                    child: const Text('Отмена'),
                                  ),
                                  TextButton(
                                    onPressed: () {
                                      _deleteStudent(student['id']);
                                      Navigator.pop(ctx);
                                    },
                                    child: const Text('Удалить'),
                                  ),
                                ],
                              ),
                            );
                          },
                        ),
                      ],
                    ),
                  ),
                );
              },
            ),
    );
  }
}