import DialogContent from '@mui/material/DialogContent';
import TextField from '@mui/material/TextField';
import Stack from '@mui/material/Stack';

function AddStudentDialogContent({ student, handleChange }) {
    return (
        <>
            <DialogContent>
                <Stack spacing={2} mt={1}>
                    <TextField data-testid="add-student-dialog-student-id" label="Student ID" name="studentId"
                        value={student.studentId} onChange={handleChange} />
                    <TextField data-testid="add-student-dialog-name" label="Name" name="name"
                        value={student.name} onChange={handleChange} />
                    <TextField data-testid="add-student-dialog-major" label="Major" name="major"
                        value={student.major} onChange={handleChange} />
                    <TextField data-testid="add-student-dialog-year" label="Year" name="year"
                        value={student.year} onChange={handleChange} />
                </Stack>
            </DialogContent>
        </>
    );
}
export default AddStudentDialogContent;