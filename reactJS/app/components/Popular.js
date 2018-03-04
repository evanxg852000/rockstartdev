import React from 'react'

import api from '../utils/api'

const SelectLanguage = (props) => {
    return(
        <ul className="languages">
            {props.languages.map((lang) => {
                return (
                    <li style={props.selected===lang? {color: '#d0021b'}: null}
                        key={lang}
                        onClick={() => props.onSelect(lang)}>
                       {lang}
                    </li>
                )
            })}
        </ul>
    )
}

const RepoGrid = (props) => {
    return (
        <ul className='popular-list'>
            {props.repos.map((repo, index) => {
                return (
                    <li key={repo.name} className='popular-item' >
                       <div className='popular-rank'>#{index + 1}</div>
                       <ul className='space-list-items'>
                            <li>
                              <img
                                className='avatar'
                                src={repo.owner.avatar_url}
                                alt={'Avatar for ' + repo.owner.login}
                              />
                            </li>
                            <li><a href={repo.html_url}>{repo.name}</a></li>
                            <li>@{repo.owner.login}</li>
                            <li>{repo.stargazers_count} stars</li>
                       </ul>
                    </li>
                )
            })}
        </ul>
    )
}

class Popular extends React.Component {

    constructor(props) {
        super(props)
        this.state = {
            languages:  ['All', 'Javscript', 'Ruby', 'Java', 'Css', 'Python'],
            selectedLanguage: 'All',
            repos: null
        }
        this.updateLanguage = this.updateLanguage.bind(this)
    }

    componentDidMount() {
        this.updateLanguage(this.state.selectedLanguage)
    }

    updateLanguage(lang) {
        api.fetchPopularRepos(lang)
            .then((items) => {
                this.setState({
                    selectedLanguage: lang,
                    repos: items
                })
            })
    }

    render() {
        return (
            <div>
                <SelectLanguage languages={this.state.languages}
                    selected={this.state.selectedLanguage}
                    onSelect={this.updateLanguage} />
                {!this.state.repos
                    ? <p>Loading ...</p>
                    : <RepoGrid repos={this.state.repos} />
                }
            </div>
        )
    }

}

export default Popular
