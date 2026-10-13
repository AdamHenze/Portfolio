export function getStudentList() {
    return [
        {
            "studentId": 12345,
            "name": "Dua Lipa",
            "major": "Art",
            "year": 4
        },
        {
            "studentId": 43632,
            "name": "Ariana Grande",
            "major": "Physics",
            "year": 3
        },
        {
            "studentId": 23095,
            "name": "Lady Gaga",
            "major": "Biology",
            "year": 2
        }
    ];
}

export function getStudentListAfterPost() {
    return [
        {
            "studentId": 12345,
            "name": "Dua Lipa",
            "major": "Art",
            "year": 4
        },
        {
            "studentId": 43632,
            "name": "Ariana Grande",
            "major": "Physics",
            "year": 3
        },
        {
            "studentId": 23095,
            "name": "Lady Gaga",
            "major": "Biology",
            "year": 2
        },
        {
            "studentId": 99999,
            "name": "Jane Doe",
            "major": "Computer Science",
            "year": 1
        }
    ];
}

export function getStudentListAfterPut() {
    return [
        {
            "studentId": 12345,
            "name": "Dua Lipa",
            "major": "Music",
            "year": 4
        },
        {
            "studentId": 43632,
            "name": "Ariana Grande",
            "major": "Physics",
            "year": 3
        },
        {
            "studentId": 23095,
            "name": "Lady Gaga",
            "major": "Biology",
            "year": 2
        }
    ];
}

export function getStudentListAfterDelete() {
    return [
        {
            "studentId": 43632,
            "name": "Ariana Grande",
            "major": "Physics",
            "year": 3
        },
        {
            "studentId": 23095,
            "name": "Lady Gaga",
            "major": "Biology",
            "year": 2
        }
    ];
}

function error() {
    return {
        statusCode: 500
    };
}