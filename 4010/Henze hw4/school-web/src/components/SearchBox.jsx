

function SearchBox({ students, setSearchResults }) {

  const handleSubmit = (e) => e.preventDefault()

  const handleSearchChange = (e) => {
    if(!e.target.value) return setSearchResults(students)

    const resultsArray = students.filter(student => student.name?.includes(e.target.value) || student.major?.includes(e.target.value))
    
    setSearchResults(resultsArray)
  }

    return (
      <div className="search-box">
        <form onSubmit={handleSubmit}>
            <input 
                className="search" 
                type="text"
                onChange={handleSearchChange}
            />
            <button>
                X    
            </button>    
        </form>        
      </div>
    );
  }
  
  export default SearchBox;