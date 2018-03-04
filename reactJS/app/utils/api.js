import axios from 'axios'

const id = 'GITHUB_CLIENT_ID'
const secret = 'GITHUB_CLIENT_SECRET'
const params = '?t=1' //`?client_id=${id}&client_secret=${secret}`

const getProfile = (username) => {
    return axios.get(`https://api.github.com/users/${username}${params}`)
        .then((user)=> user.data)
}

const getRepos = (username) => {
    return axios.get(`https://api.github.com/users/${username}/repos${params}&per_page=100`)
}

const getStarCount = (repos) => {
    return repos.reduce((acc, repo) => {
        return acc + repo.stargazers_count
    }, 0)
}

const calculateScore = (profile, repos) => {
    let followers = profile.followers
    let totalStars = getStarCount(repos)
    console.log('Evan', followers, totalStars)
    return (followers * 3) + totalStars
}

const getUserData = (player) => {
    return Promise.all([
        getProfile(player),
        getRepos(player)
    ]).then((data) => {
        console.log(data)
        let profile = data[0]
        let repos = data[1].data
        return {
            profile: profile,
            score: calculateScore(profile, repos)
        }
    })
}

const sortPlayers = (players) => {
    return players.sort((a,b) => b.score - a.score)
}

const Api = {
    battle(players) {
        return Promise.all(players.map(getUserData))
            .then(sortPlayers)
            .catch(console.warn)
    },

    fetchPopularRepos(language) {
        let encodedURI = window.encodeURI('https://api.github.com/search/repositories?q=stars:>1+language:'+ language + '&sort=stars&order=desc&type=Repositories')
        return axios.get(encodedURI)
            .then((resp) => resp.data.items )
    }


}

export default Api
