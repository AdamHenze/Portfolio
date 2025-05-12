import {getStudentList, getStudentListAfterPost,getStudentListAfterPut, getStudentListAfterDelete} from '../mocks/mock-student';

describe('student table', () => {

  beforeEach(() => {
    cy.intercept(
      {
        method: 'GET',
        url: '/student'
      },
      getStudentList()
    ).as('getRequest');

  });

  it.only('should display student table', () => {
    cy.visit('http://localhost:3000');

    cy.get('[data-testid="student-table"]').should('exist');
    cy.get('[data-testid="student-table"]').find('.MuiDataGrid-row').should('have.length', 3); // must have 3 rows

  });

  it('should display initial row data', () => {
    cy.visit('http://localhost:3000');

    // Get all rows in DataGrid
    cy.get('[data-testid="student-table"]').find('.MuiDataGrid-row').each(($row, index) => {
      switch (index) {
        case 0: // first row
          // Get columns (cells) within the row
          cy.wrap($row).find('.MuiDataGrid-cell').each(($cell, cellIndex) => {
            // Assert the content of each cell (column) in the row
            if (cellIndex === 0) cy.wrap($cell).should('contain.text', '12345'); 
            if (cellIndex === 1) cy.wrap($cell).should('contain.text', 'Dua Lipa'); 
            if (cellIndex === 2) cy.wrap($cell).should('contain.text', 'Art'); 
            if (cellIndex === 3) cy.wrap($cell).should('contain.text', '4'); 
          });
          break;
        case 1: // second row
          // Get columns (cells) within the row
          cy.wrap($row).find('.MuiDataGrid-cell').each(($cell, cellIndex) => {
            // Assert the content of each cell (column) in the row
            if (cellIndex === 0) cy.wrap($cell).should('contain.text', '43632'); 
            if (cellIndex === 1) cy.wrap($cell).should('contain.text', 'Ariana Grande'); 
            if (cellIndex === 2) cy.wrap($cell).should('contain.text', 'Physics'); 
            if (cellIndex === 3) cy.wrap($cell).should('contain.text', '3'); 
          });
          break;
        case 2: // third row
          // Get columns (cells) within the row
          cy.wrap($row).find('.MuiDataGrid-cell').each(($cell, cellIndex) => {
            // Assert the content of each cell (column) in the row
            if (cellIndex === 0) cy.wrap($cell).should('contain.text', '23095'); 
            if (cellIndex === 1) cy.wrap($cell).should('contain.text', 'Lady Gaga'); 
            if (cellIndex === 2) cy.wrap($cell).should('contain.text', 'Biology'); 
            if (cellIndex === 3) cy.wrap($cell).should('contain.text', '2'); 
          });
          break;
      }
    });

  });

  it('should display add student button', () => {
    cy.visit('http://localhost:3000');

    cy.get('[data-testid="add-student-button"]').should('exist');
    cy.get('[data-testid="add-student-button"]').should('contain.text', 'Add Student');
  });

  it('should open add student dialog', () => {
    cy.visit('http://localhost:3000');

    cy.get('[data-testid="add-student-button"]').click();
    cy.get('[data-testid="add-student-dialog"]').should('be.visible');
    cy.get('[data-testid="add-student-dialog-student-id"]').should('exist').and('be.visible');
    cy.get('[data-testid="add-student-dialog-name"]').should('exist').and('be.visible');
    cy.get('[data-testid="add-student-dialog-major"]').should('exist').and('be.visible');
    cy.get('[data-testid="add-student-dialog-year"]').should('exist').and('be.visible');
  });

  it('should add a new row', () => {
    cy.visit('http://localhost:3000');

    cy.get('[data-testid="add-student-button"]').click();

    cy.get('[data-testid="add-student-dialog-student-id"]').type('99999');
    cy.get('[data-testid="add-student-dialog-name"]').type('Jane Doe');
    cy.get('[data-testid="add-student-dialog-major"]').type('Computer Science');
    cy.get('[data-testid="add-student-dialog-year"]').type('1');

    cy.intercept(
      {
        url: '/student'
      },
      getStudentListAfterPost()
    );

    cy.get('[data-testid="add-student-save"]').click();

    cy.get('[data-testid="student-table"]').find('.MuiDataGrid-row').each(($row, index) => {
      switch (index) {
        case 3: // fourth row
          // Get columns (cells) within the row
          cy.wrap($row).find('.MuiDataGrid-cell').each(($cell, cellIndex) => {
            // Assert the content of each cell (column) in the row
            if (cellIndex === 0) cy.wrap($cell).should('contain.text', '99999'); 
            if (cellIndex === 1) cy.wrap($cell).should('contain.text', 'Jane Doe'); 
            if (cellIndex === 2) cy.wrap($cell).should('contain.text', 'Computer Science'); 
            if (cellIndex === 3) cy.wrap($cell).should('contain.text', '1'); 
          });
          break;
      }
    });
  });

  it('should edit an existing row', () => {
    cy.visit('http://localhost:3000');

    cy.get('[data-testid="edit-button-row-12345"]').click();

    cy.get('[data-testid="edit-student-dialog-major"]').type('Music');

    cy.intercept(
      {
        method: 'PUT',
        url: '/student/*'
      },
      getStudentListAfterPut()
    );
    cy.intercept(
      {
        method: 'GET',
        url: '/student'
      },
      getStudentListAfterPut()
    );

    cy.get('[data-testid="edit-student-save"]').click();

    cy.get('[data-testid="student-table"]').find('.MuiDataGrid-row').each(($row, index) => {
      switch (index) {
        case 0: // first row
          // Get columns (cells) within the row
          cy.wrap($row).find('.MuiDataGrid-cell').each(($cell, cellIndex) => {
            // Assert the content of each cell (column) in the row
            if (cellIndex === 0) cy.wrap($cell).should('contain.text', '12345'); 
            if (cellIndex === 1) cy.wrap($cell).should('contain.text', 'Dua Lipa'); 
            if (cellIndex === 2) cy.wrap($cell).should('contain.text', 'Music'); 
            if (cellIndex === 3) cy.wrap($cell).should('contain.text', '4'); 
          });
          break;
      }
    });
  });

  it('should delete an existing row', () => {
    cy.visit('http://localhost:3000');

    cy.intercept(
      {
        method: 'DELETE',
        url: '/student/12345'
      },
      getStudentListAfterDelete()
    );
    cy.intercept(
      {
        method: 'GET',
        url: '/student'
      },
      getStudentListAfterDelete()
    );

    cy.get('[data-testid="delete-button-row-12345"]').click();

    cy.get('[data-testid="student-table"]').find('.MuiDataGrid-row').should('have.length', 2); // must have 2 rows
  });

});