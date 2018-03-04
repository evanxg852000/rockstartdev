import React from 'react'
import {BrowserRouter, Route, Switch} from 'react-router-dom'

import Nav from './Nav'
import Home from './Home'
import Battle from './Battle'
import Results from './Results'
import Popular from './Popular'


class App extends React.Component {
    render() {
       return (
            <BrowserRouter>
                <div className="container">
                    <Nav />
                    <Switch>
                        <Route exact path='/' component={Home} />
                        <Route exact path='/battle' component={Battle} />
                        <Route path='/battle/results' component={Results} />
                        <Route path='/popular' component={Popular} />
                        <Route render={()=>{
                            return (<p>Not Found!</p>)
                        }} />
                    </Switch>
               </div>
            </BrowserRouter>
       )
    }
}

export default App
