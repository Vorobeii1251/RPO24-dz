<?php
header('Content-Type: application/json; charset=utf-8');

// Настройки подключения к БД
$host = 'localhost';
$user = 'root';
$password = '';
$database = 'flutter_db';

$conn = new mysqli($host, $user, $password, $database);
$conn->set_charset("utf8");

if ($conn->connect_error) {
    die(json_encode(['error' => 'Connection failed: ' . $conn->connect_error]));
}

$action = $_POST['action'] ?? '';
$response = ['success' => false];

switch ($action) {
    case 'read':
        $sort = $_POST['sort'] ?? 'name';
        
        if ($sort === 'score') {
            $sql = "SELECT * FROM students ORDER BY average_score DESC";
        } else {
            $sql = "SELECT * FROM students ORDER BY name ASC";
        }
        
        $result = $conn->query($sql);
        $students = [];
        
        while ($row = $result->fetch_assoc()) {
            $students[] = [
                'id' => (int)$row['id'],
                'name' => $row['name'],
                'group' => $row['group_num'],
                'score' => (float)$row['average_score']
            ];
        }
        
        $response = ['success' => true, 'students' => $students];
        break;
        
    case 'create':
        $name = $_POST['name'] ?? '';
        $group = $_POST['group'] ?? '';
        $score = $_POST['score'] ?? '';
        
        if ($name && $group && $score) {
            $stmt = $conn->prepare("INSERT INTO students (name, group_num, average_score) VALUES (?, ?, ?)");
            $stmt->bind_param("ssd", $name, $group, $score);
            
            if ($stmt->execute()) {
                $response = ['success' => true, 'id' => $stmt->insert_id];
            } else {
                $response = ['success' => false, 'error' => $stmt->error];
            }
            $stmt->close();
        }
        break;
        
    case 'update':
        $id = (int)($_POST['id'] ?? 0);
        $name = $_POST['name'] ?? '';
        $group = $_POST['group'] ?? '';
        $score = $_POST['score'] ?? '';
        
        if ($id && $name && $group && $score) {
            $stmt = $conn->prepare("UPDATE students SET name = ?, group_num = ?, average_score = ? WHERE id = ?");
            $stmt->bind_param("ssdi", $name, $group, $score, $id);
            
            if ($stmt->execute()) {
                $response = ['success' => true];
            } else {
                $response = ['success' => false, 'error' => $stmt->error];
            }
            $stmt->close();
        }
        break;
        
    case 'delete':
        $id = (int)($_POST['id'] ?? 0);
        
        if ($id) {
            $stmt = $conn->prepare("DELETE FROM students WHERE id = ?");
            $stmt->bind_param("i", $id);
            
            if ($stmt->execute()) {
                $response = ['success' => true];
            } else {
                $response = ['success' => false, 'error' => $stmt->error];
            }
            $stmt->close();
        }
        break;
        
    default:
        $response = ['success' => false, 'error' => 'Unknown action'];
}

$conn->close();
echo json_encode($response);
?>