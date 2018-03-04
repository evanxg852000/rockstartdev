import React from 'react'

const PlayerPreview = (props) => {
    return (
        <div>
            <div className='column'>
                <img className='avatar' src={props.avatar} alt={'Avatar for ' + props.username} />
                <h2 className='username'>@{props.username}</h2>
            </div>
            {props.children}
        </div>
    )
}

export default PlayerPreview
