import EditIcon from '@mui/icons-material/Edit';
import Button from '@mui/material/Button';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogTitle from '@mui/material/DialogTitle';
import IconButton from '@mui/material/IconButton';
import Tooltip from '@mui/material/Tooltip';
import axios from 'axios';
import { useState } from 'react';
import { API_URL } from "../api/studentAPI";
import EditStudentDialogContent from './EditStudentDialogContent';

function EditStudent({ studentData, setStudents }) {

    const [open, setOpen] = useState(false); // initially hide edit diaglog window
    const [student, setStudent] = useState({
        studentId: '',
        name: '',
        major: '',
        year: 0
    });

    const handleClickOpen = () => {
        setOpen(true); // display edit diaglog window
        setStudent({
            studentId: studentData.studentId,
            name: studentData.name,
            major: studentData.major,
            year: studentData.year
        });
    };

    const handleClose = () => {
        setOpen(false); // close edit dialog window
    };

    const fetchStudents = async () => {
        const response = await axios.get(`${API_URL}`); // returns Promise

        console.log(response.data);
        setStudents(response.data);
    };

    const editStudent = async (studentId, student) => {
        await axios.put(`${API_URL}/${studentId}`, student);
        fetchStudents();
    };

    const handleSave = () => {
        editStudent(studentData.studentId, student);
        setStudent({ studentId: '', name: '', major: '', year: 0 });
        setOpen(false); // close edit dialog window
    }

    const handleChange = (event) => {
        setStudent({ ...student, [event.target.name]: event.target.value });
    }

    return (
        <>
            <Tooltip title="Edit Student">
                <IconButton data-testid={`edit-button-row-${studentData.studentId}`} aria-label="edit" size="small" onClick={handleClickOpen}>
                    <EditIcon fontSize="small" />
                </IconButton>
            </Tooltip>
            <Dialog open={open} onClose={handleClose}>
                <DialogTitle>Edit Student</DialogTitle>
                <EditStudentDialogContent student={student} handleChange={handleChange} />
                <DialogActions>
                    <Button onClick={handleClose}>Cancel</Button>
                    <Button data-testid="edit-student-save" onClick={handleSave}>Save</Button>
                </DialogActions>
            </Dialog>
        </>
    );
}

export default EditStudent;