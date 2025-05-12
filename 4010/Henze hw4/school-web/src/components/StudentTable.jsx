import DeleteIcon from '@mui/icons-material/Delete';
import IconButton from '@mui/material/IconButton';
import Tooltip from '@mui/material/Tooltip';
import { DataGrid } from '@mui/x-data-grid';
import { useEffect, useState } from "react";
import axios from "axios";
import { API_URL } from "../api/studentAPI";
import AddStudent from "./AddStudent";
import EditStudent from "./EditStudent";
import "./StudentTable.css";
import SearchBox from './SearchBox';

function StudentTable() {
  const [students, setStudents] = useState([]);
  const [searchResults, setSearchResults] = useState([])

  const fetchStudents = async () => {
    const response = await axios.get(`${API_URL}`); // returns Promise

    console.log(response.data);
    setStudents(response.data);
    setSearchResults(response.data);
  };

  const deleteStudent = async (studentId) => {
    await axios.delete(`${API_URL}/${studentId}`);
    fetchStudents();
  };

  useEffect(() => {
    fetchStudents();
  }, []);

  const handleClickDelete = (studentId) => {
    deleteStudent(studentId);
  }

  const columns = [
    { field: 'studentId', headerName: 'Student ID', width: 120, headerAlign: 'center', align: 'center', headerClassName: 'custom-header' },
    { field: 'name', headerName: 'Name', width: 180, headerAlign: 'center', align: 'center', headerClassName: 'custom-header' },
    { field: 'major', headerName: 'Major', width: 180, headerAlign: 'center', align: 'center', headerClassName: 'custom-header' },
    { field: 'year', headerName: 'Year', width: 80, headerAlign: 'center', align: 'center', headerClassName: 'custom-header' },
    {
      field: 'edit',
      headerName: '',
      width: 80,
      sortable: false,
      filterable: false,
      disableColumnMenu: true,
      headerClassName: 'custom-header',
      headerAlign: 'center',
      align: 'center',
      renderCell: (params) =>
        <EditStudent studentData={params.row} setStudents={setStudents} />
    },
    {
      field: 'delete',
      headerName: '',
      width: 80,
      sortable: false,
      filterable: false,
      disableColumnMenu: true,
      headerClassName: 'custom-header',
      headerAlign: 'center',
      align: 'center',
      renderCell: (params) => (
        <Tooltip data-testid={`delete-button-row-${params.row.studentId}`} title="Delete Student">
          <IconButton aria-label="delete" size="small" onClick={() => handleClickDelete(params.row.studentId)}>
            <DeleteIcon fontSize="small" />
          </IconButton>
        </Tooltip>
      ),
    },
  ];

  return (
    <div className="bg-container">
      <div className="tbl-container">
        <div>
          <SearchBox students={students} setSearchResults={setSearchResults}/>
        </div>
        <div className="btn-container">
          <AddStudent setStudents={setStudents}/>
        </div>
        <DataGrid data-testid="student-table"
          rows={searchResults}
          columns={columns}
          disableRowSelectionOnClick={true}
          getRowId={row => row.studentId}
          getRowClassName={(params) =>
            params.indexRelativeToCurrentPage % 2 === 0 ? 'hot' : 'cold'
          }
          sx={{
            boxShadow: 2,
            '& .MuiDataGrid-cell:hover': {
              color: 'primary.main',
            },
            '& .cold': {
              backgroundColor: '#e7f0f7',
              color: 'black',
            },
            '& .hot': {
              backgroundColor: '#ccdfef',
              color: 'black',
            },
          }}
        />
      </div>
    </div>
  );
}

export default StudentTable;