import React from 'react'
import {Link} from 'react-router-dom'

import PlayerPreview from './PlayerPreview'

class PlayerInput extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            username: ''
        }
        this.handleChange = this.handleChange.bind(this)
        this.handleSubmit = this.handleSubmit.bind(this)
    }

    handleChange(evt) {
        this.setState({
            username: evt.target.value
        })
    }

    handleSubmit(evt) {
        evt.preventDefault()
        this.props.onSubmit(this.props.id, this.state.username)
    }

    render() {
        return (
            <form className='column' onSubmit={this.handleSubmit}>
                <label className='header' htmlFor='username'>{this.props.label}</label>
                <input
                  id='username'
                  placeholder='Github username'
                  type='text'
                  value={this.state.username}
                  autoComplete='off'
                  onChange={this.handleChange}
                />
                <button
                  className='button'
                  type='submit'
                  disabled={!this.state.username}>
                    Submit
                </button>
            </form>
        )
    }

}

class Battle extends React.Component {
    constructor(props) {
        super(props)
        this.state  = {
            playerOneName: '',
            playerOneImage: null,
            playerTwoName: '',
            playerTwoImage: null,

        }
        this.handleSubmit = this.handleSubmit.bind(this)
        this.handleReset = this.handleReset.bind(this)
    }

    handleSubmit(id, username) {
        this.setState({
            [`${id}Name`]: username,
            [`${id}Image`]: `https://github.com/${username}.png?size=200`
        })
    }

    handleReset(id) {
        this.setState({
            [`${id}Name`]: '',
            [`${id}Image`]: null
        })
    }

    render() {
        let match = this.props.match
        let playerOneName = this.state.playerOneName
        let playerOneImage = this.state.playerOneImage
        let playerTwoName = this.state.playerTwoName
        let playerTwoImage = this.state.playerTwoImage
        return (
            <div>
                <div className='row'>
                      {!playerOneName &&
                        <PlayerInput
                          id='playerOne'
                          label='Player One'
                          onSubmit={this.handleSubmit}/>
                      }
                     {playerOneImage &&
                        <PlayerPreview
                          avatar={playerOneImage}
                          username={playerOneName}>
                            <button
                              className='reset'
                              onClick={() => this.handleReset('playerOne')}>
                                Reset
                            </button>
                        </PlayerPreview>
                      }
                      {!playerTwoName &&
                        <PlayerInput
                          id='playerTwo'
                          label='Player Two'
                          onSubmit={this.handleSubmit} />
                      }
                      {playerTwoImage &&
                        <PlayerPreview
                          avatar={playerTwoImage}
                          username={playerTwoName}>
                            <button
                              className='reset'
                              onClick={() => this.handleReset('playerTwo')}>
                                Reset
                            </button>
                        </PlayerPreview>
                      }
                </div>
                  {playerOneImage && playerTwoImage &&
                      <Link className='button'
                        to={{ pathname: match.url + '/results',
                            search: '?playerOneName=' + playerOneName + '&playerTwoName=' + playerTwoName}}>
                          Battle
                      </Link>
                  }
            </div>
        )
    }
}


export default Battle
