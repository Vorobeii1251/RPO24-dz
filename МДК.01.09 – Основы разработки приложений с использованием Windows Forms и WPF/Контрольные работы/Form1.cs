using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Windows.Forms;

namespace PhoneBook
{
    public partial class MainForm : Form
    {
        private BindingList<Contact> contacts = new BindingList<Contact>();

        private readonly string dataFile = "contacts.json";

        public MainForm()
        {
            InitializeComponent();
            LoadContacts();
            SetupDataGridView();
            UpdateStatus();
        }

        private void SetupDataGridView()
        {
            var bindingSource = new BindingSource();
            bindingSource.DataSource = contacts;
            dataGridViewContacts.DataSource = bindingSource;

            if (dataGridViewContacts.Columns.Count > 0)
            {
                dataGridViewContacts.Columns["FirstName"].HeaderText = "Имя";
                dataGridViewContacts.Columns["LastName"].HeaderText = "Фамилия";
                dataGridViewContacts.Columns["Phone"].HeaderText = "Телефон";
                dataGridViewContacts.Columns["Email"].HeaderText = "Email";
                dataGridViewContacts.Columns["FullName"].Visible = false; 

                dataGridViewContacts.Columns["FirstName"].Width = 120;
                dataGridViewContacts.Columns["LastName"].Width = 120;
                dataGridViewContacts.Columns["Phone"].Width = 130;
                dataGridViewContacts.Columns["Email"].Width = 150;
            }

            dataGridViewContacts.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewContacts.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridViewContacts.MultiSelect = false;
            dataGridViewContacts.AllowUserToAddRows = false;
        }

        private void LoadContacts()
        {
            if (!File.Exists(dataFile))
                return;

            try
            {
                string json = File.ReadAllText(dataFile);
                var loadedContacts = JsonSerializer.Deserialize<List<Contact>>(json);
                if (loadedContacts != null)
                {
                    contacts.Clear();
                    foreach (var contact in loadedContacts)
                        contacts.Add(contact);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка загрузки файла: {ex.Message}", "Ошибка",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void SaveContacts()
        {
            try
            {
                var list = contacts.ToList();
                string json = JsonSerializer.Serialize(list, new JsonSerializerOptions { WriteIndented = true });
                File.WriteAllText(dataFile, json);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка сохранения файла: {ex.Message}", "Ошибка",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtFirstName.Text) && string.IsNullOrWhiteSpace(txtLastName.Text))
            {
                MessageBox.Show("Введите имя или фамилию!", "Предупреждение",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (string.IsNullOrWhiteSpace(txtPhone.Text))
            {
                MessageBox.Show("Введите номер телефона!", "Предупреждение",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            var contact = new Contact
            {
                FirstName = txtFirstName.Text.Trim(),
                LastName = txtLastName.Text.Trim(),
                Phone = txtPhone.Text.Trim(),
                Email = txtEmail.Text.Trim()
            };

            contacts.Add(contact);

            txtFirstName.Clear();
            txtLastName.Clear();
            txtPhone.Clear();
            txtEmail.Clear();

            UpdateStatus();
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (dataGridViewContacts.CurrentRow == null)
            {
                MessageBox.Show("Выберите контакт для удаления!", "Информация",
                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            var contact = dataGridViewContacts.CurrentRow.DataBoundItem as Contact;
            if (contact == null) return;

            var result = MessageBox.Show($"Удалить контакт \"{contact.FullName}\"?",
                "Подтверждение", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

            if (result == DialogResult.Yes)
            {
                contacts.Remove(contact);
                UpdateStatus();
            }
        }

        private void txtSearch_TextChanged(object sender, EventArgs e)
        {
            string filter = txtSearch.Text.Trim().ToLower();

            if (string.IsNullOrEmpty(filter))
            {
                ((BindingSource)dataGridViewContacts.DataSource).RemoveFilter();
            }
            else
            {
                ((BindingSource)dataGridViewContacts.DataSource).Filter =
                    $"FirstName LIKE '%{filter}%' OR " +
                    $"LastName LIKE '%{filter}%' OR " +
                    $"Phone LIKE '%{filter}%' OR " +
                    $"Email LIKE '%{filter}%'";
            }

            UpdateStatus();
        }

        private void UpdateStatus()
        {
            var bindingSource = (BindingSource)dataGridViewContacts.DataSource;
            int totalCount = contacts.Count;
            int displayedCount = bindingSource.Count;

            if (totalCount == displayedCount)
                toolStripStatusLabel.Text = $"Всего контактов: {totalCount}";
            else
                toolStripStatusLabel.Text = $"Показано: {displayedCount} из {totalCount}";
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            SaveContacts();
        }

        private void dataGridViewContacts_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0) return;

            var contact = dataGridViewContacts.Rows[e.RowIndex].DataBoundItem as Contact;
            if (contact != null)
            {
                txtFirstName.Text = contact.FirstName;
                txtLastName.Text = contact.LastName;
                txtPhone.Text = contact.Phone;
                txtEmail.Text = contact.Email;

                contacts.Remove(contact);
                MessageBox.Show("Внесите изменения и нажмите 'Добавить'", "Редактирование",
                    MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
    }
}