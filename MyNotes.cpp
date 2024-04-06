#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Notes 
{
private:
    map<string, vector<string>> subjectNotes;

public:
    void addNote(const string& subject, const vector<string>& notes) 
	{
        subjectNotes[subject].insert(subjectNotes[subject].end(), notes.begin(), notes.end());
    }

    void displayNotes(const string& subject) const 
	{
        auto it = subjectNotes.find(subject);
        if (it != subjectNotes.end()) 
		{
            cout << "Notes for Subject '" << subject << "':\n";
            for (const auto& note : it->second)
			{
                cout << " - " << note << "\n";
            }
        } else 
		{
            cout << "No notes found for Subject '" << subject << "'.\n";
        }
    }

    void displayAllNotes() const 
	{
        cout << "All Subject-wise Notes:\n";
        for (const auto& pair : subjectNotes) 
		{
            cout << "Subject: " << pair.first << "\n";
            for (const auto& note : pair.second)
			{
                cout << " - " << note << "\n";
            }
        }
    }

    void saveNotesToFile(const string& username) const 
	{
        ofstream file(username + "_notes.txt");
        for (const auto& pair : subjectNotes) 
		{
            file << pair.first << ":\n";
            for (const auto& note : pair.second) 
			{
                file << note << "\n";
            }
            file << '\n';
        }
        file.close();
    }

    void loadNotesFromFile(const string& username)
	 {
        ifstream file(username + "_notes.txt");
        if (file.is_open()) 
		{
            string line;
            string currentSubject;
            vector<string> currentNotes;
            while (getline(file, line)) 
			{
                if (line.back() == ':') 
				{
                    currentSubject = line.substr(0, line.size() - 1);
                    currentNotes.clear();
                } else if (!line.empty()) 
				{
                    currentNotes.push_back(line);
                    subjectNotes[currentSubject] = currentNotes;
                }
            }
            file.close();
        }
    }
};

class User 
{	
private:
    string username;
    string password;
    Notes userNotes;

public:
    User(const string& uname, const string& pwd)
        : username(uname), password(pwd) {}

    bool login(const string& enteredPassword) const 
	{
        return password == enteredPassword;
    }

    void addNote() 
	{
        string subject, note;
        vector<string> notes;
        cout << "Enter subject: ";
        cin >> subject;
        cin.ignore(); // Clear newline character from the buffer
        cout << "Enter notes for " << subject << " (end input with 'end' on a new line):\n";
        while (getline(cin, note)) 
		{
            if (note == "end") 
			{
                break;
            }
            notes.push_back(note);
        }
        userNotes.addNote(subject, notes);
    }

    void viewNotes() const 
	{
        string subject;
        cout << "Enter subject to view notes: ";
        cin >> subject;
        userNotes.displayNotes(subject);
    }

    void viewAllNotes() const 
	{
        userNotes.displayAllNotes();
    }

    void saveNotes() const 
	{
        userNotes.saveNotesToFile(username);
    }

    void loadNotes() 
	{
        userNotes.loadNotesFromFile(username);
    }
};

int main() 
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User user(username, password);

    // Simulating login (In a real application, you would validate the login credentials)
    string enteredPassword;
    cout << "Enter password to login: ";
    cin >> enteredPassword;

    if (user.login(enteredPassword)) 
	{
        cout << "Login successful!\n";

        // Load existing notes
        user.loadNotes();

        int choice;
        do 
		{
            cout << "\nMenu:\n"
                 << "1. Add Note\n"
                 << "2. View Notes for a Subject\n"
                 << "3. View All Notes\n"
                 << "4. Save Notes\n"
                 << "5. Load Notes\n"
                 << "6. Exit\n"
                 << "Enter your choice: ";
            cin >> choice;

            switch (choice) 
			{	
                case 1:
                    user.addNote();
                    break;
                case 2:
                    user.viewNotes();
                    break;
                case 3:
                    user.viewAllNotes();
                    break;
                case 4:
                    user.saveNotes();
                    break;
                case 5:
                    user.loadNotes();
                    cout << "Notes loaded.\n";
                    break;
                case 6:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 6);
    }
	else 
	{
        cout << "Login failed. Incorrect password.\n";
    }

    return 0;
}
